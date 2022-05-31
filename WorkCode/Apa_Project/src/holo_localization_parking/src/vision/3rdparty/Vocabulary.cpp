#include <sstream>
#include <holo/localization/vision/3rdparty/Vocabulary.h>

namespace DBoW3{
// --------------------------------------------------------------------------


Vocabulary::Vocabulary
  (int k, int L, WeightingType weighting, ScoringType scoring)
  : m_k(k), m_L(L), m_weighting(weighting), m_scoring(scoring),
  m_scoring_object(NULL)
{
  createScoringObject();
}

// --------------------------------------------------------------------------


Vocabulary::Vocabulary
  (const std::string &filename): m_scoring_object(NULL)
{
  load(filename);
}

// --------------------------------------------------------------------------


Vocabulary::Vocabulary
  (const char *filename): m_scoring_object(NULL)
{
  load(filename);
}

// --------------------------------------------------------------------------


void Vocabulary::createScoringObject()
{
  delete m_scoring_object;
  m_scoring_object = NULL;

  switch(m_scoring)
  {
    case L1_NORM:
      m_scoring_object = new L1Scoring;
      break;

    case L2_NORM:
      m_scoring_object = new L2Scoring;
      break;

    case CHI_SQUARE:
      m_scoring_object = new ChiSquareScoring;
      break;

    case KL:
      m_scoring_object = new KLScoring;
      break;

    case BHATTACHARYYA:
      m_scoring_object = new BhattacharyyaScoring;
      break;

    case DOT_PRODUCT:
      m_scoring_object = new DotProductScoring;
      break;

  }
}

// --------------------------------------------------------------------------


void Vocabulary::setScoringType(ScoringType type)
{
  m_scoring = type;
  createScoringObject();
}

// --------------------------------------------------------------------------


void Vocabulary::setWeightingType(WeightingType type)
{
  this->m_weighting = type;
}

// --------------------------------------------------------------------------


Vocabulary::Vocabulary(
  const Vocabulary &voc)
  : m_scoring_object(NULL)
{
  *this = voc;
}

// --------------------------------------------------------------------------


Vocabulary::~Vocabulary()
{
  delete m_scoring_object;
}

// --------------------------------------------------------------------------


Vocabulary&
Vocabulary::operator=
  (const Vocabulary &voc)
{
  this->m_k = voc.m_k;
  this->m_L = voc.m_L;
  this->m_scoring = voc.m_scoring;
  this->m_weighting = voc.m_weighting;

  this->createScoringObject();

  this->m_nodes.clear();
  this->m_words.clear();

  this->m_nodes = voc.m_nodes;
  this->createWords();

  return *this;
}



void Vocabulary::create(
  const std::vector< cv::Mat > &training_features)
{
    std::vector<std::vector<cv::Mat> > vtf(training_features.size());
    for(size_t i=0;i<training_features.size();i++){
        vtf[i].resize(training_features[i].rows);
        for(int r=0;r<training_features[i].rows;r++)
            vtf[i][r]=training_features[i].rowRange(r,r+1);
    }
    create(vtf);

}

void Vocabulary::create(
  const std::vector<std::vector<cv::Mat> > &training_features)
{
  m_nodes.clear();
  m_words.clear();

  // expected_nodes = Sum_{i=0..L} ( k^i )
    int expected_nodes =
        (int)((pow((double)m_k, (double)m_L + 1) - 1)/(m_k - 1));

  m_nodes.reserve(expected_nodes); // avoid allocations when creating the tree


  std::vector<cv::Mat> features;
  getFeatures(training_features, features);


  // create root
  m_nodes.push_back(Node(0)); // root

  // create the tree
  HKmeansStep(0, features, 1);

  // create the words
  createWords();

  // and set the weight of each node of the tree
  setNodeWeights(training_features);

}

// --------------------------------------------------------------------------


void Vocabulary::create(
  const std::vector<std::vector<cv::Mat> > &training_features,
  int k, int L)
{
  m_k = k;
  m_L = L;

  create(training_features);
}

// --------------------------------------------------------------------------


void Vocabulary::create(
  const std::vector<std::vector<cv::Mat> > &training_features,
  int k, int L, WeightingType weighting, ScoringType scoring)
{
  m_k = k;
  m_L = L;
  m_weighting = weighting;
  m_scoring = scoring;
  createScoringObject();

  create(training_features);
}

// --------------------------------------------------------------------------


void Vocabulary::getFeatures(
  const std::vector<std::vector<cv::Mat> > &training_features,
  std::vector<cv::Mat> &features) const
{
  features.resize(0);
  for(size_t i=0;i<training_features.size();i++)
      for(size_t j=0;j<training_features[i].size();j++)
              features.push_back(training_features[i][j]);
}

// --------------------------------------------------------------------------


void Vocabulary::HKmeansStep(NodeId parent_id,
                             const std::vector<cv::Mat> &descriptors, int current_level)
{

    if(descriptors.empty()) return;

    /**
     *下面的两行代码想表达这样一个意思：
     *  [1] 聚类中心的个数，每个聚类中心拥有自己的描述子
     *  [2] 每个类中包含所有的 descriptors，以表示该 Descriptor 属于当前的哪一个类
     *  [3] groups[i] = [j1, j2, ...], i -> 类别的索引, K-Means 形成了多个类，　j1, j2, .... 表示属于该类的描述子
     */
    // features associated to each cluster
    std::vector<cv::Mat> clusters;
    std::vector<std::vector<unsigned int> > groups; // groups[i] = [j1, j2, ...]
    // j1, j2, ... indices of descriptors associated to cluster i

    clusters.reserve(m_k);
    groups.reserve(m_k);


    if((int)descriptors.size() <= m_k)
    {
        // trivial case: one cluster per feature
        groups.resize(descriptors.size());

        for(unsigned int i = 0; i < descriptors.size(); i++)
        {
            groups[i].push_back(i);
            clusters.push_back(descriptors[i]);
        }
    }
    else
    {
        // select clusters and groups with kmeans

        bool first_time = true;
        bool goon = true;

        // to check if clusters move after iterations
        std::vector<int> last_association, current_association;

        while(goon)
        {
            // 1. Calculate clusters

            // 在首次迭代时，使用 k-menans++ 的方法先确定聚类中心 K 的数量
            if(first_time)
            {
                // random sample
                initiateClusters(descriptors, clusters);
            }
            // 非首次迭代时
            else
            {
                // calculate cluster centres

                // 使用属于该类所有描述子的均值，作为该类新的聚类中心
                for(unsigned int c = 0; c < clusters.size(); ++c)
                {
                    std::vector<cv::Mat> cluster_descriptors;
                    cluster_descriptors.reserve(groups[c].size());
                    std::vector<unsigned int>::const_iterator vit;
                    for(vit = groups[c].begin(); vit != groups[c].end(); ++vit)
                    {
                        cluster_descriptors.push_back(descriptors[*vit]);
                    }

                    DescManip::meanValue(cluster_descriptors, clusters[c]);
                }

            } // if(!first_time)

            // 2. Associate features with clusters

            // calculate distances to cluster centers
            groups.clear();
            groups.resize(clusters.size(), std::vector<unsigned int>());
            current_association.resize(descriptors.size());

            //assoc.clear();

            //unsigned int d = 0;
            /**
             * 该 for 循环做了两件事：
             *      [1] 为每一个描述子找到距离它最近的聚类中心
             *      [2] 更新每个聚类存储的描述子索引 `groups`， 更新每个描述子所属的类 `current_association`
             */
            for(auto  fit = descriptors.begin(); fit != descriptors.end(); ++fit)//, ++d)
            {
                double best_dist = DescManip::distance((*fit), clusters[0]);
                unsigned int icluster = 0;

                // 找到距离当前描述子最近的中心 (K)
                for(unsigned int c = 1; c < clusters.size(); ++c)
                {
                    double dist = DescManip::distance((*fit), clusters[c]);
                    if(dist < best_dist)
                    {
                        best_dist = dist;
                        icluster = c;
                    }
                }

                //assoc.ref<unsigned char>(icluster, d) = 1;

                // 更新每个类 groups[i] 包含了描述子，i 表示类别的索引，　索引值代表其包含的描述子
                // 更新当前描述子的分配情况 current_association[j]，ｊ 表示描述子的索引，值代表其对应的聚类中心
                groups[icluster].push_back(fit - descriptors.begin());
                current_association[ fit - descriptors.begin() ] = icluster;
            }

            // kmeans++ ensures all the clusters has any feature associated with them

            // 3. check convergence
            // 当属于每个类的描述子不再发生变换时，认为当前迭代已经完成
            if(first_time)
            {
                first_time = false;
            }
            else
            {
                //goon = !eqUChar(last_assoc, assoc);

                goon = false;
                for(unsigned int i = 0; i < current_association.size(); i++)
                {
                    if(current_association[i] != last_association[i]){
                        goon = true;
                        break;
                    }
                }
            }

            // 进入下次迭代计算
            if(goon)
            {
                // copy last feature-cluster association
                last_association = current_association;
                //last_assoc = assoc.clone();
            }

        } // while(goon)

    } // if must run kmeans

    // create nodes
    // 将当前层的聚类中心作为节点加入到整个词袋树中，作为树的一个节点, 
    // 注意学习这里的存储方法，整个 vector 是按照树的每层进行存储的
    for(unsigned int i = 0; i < clusters.size(); ++i)
    {
        NodeId id = m_nodes.size();
        m_nodes.push_back(Node(id));
        m_nodes.back().descriptor = clusters[i];
        m_nodes.back().parent = parent_id;
        m_nodes[parent_id].children.push_back(id);
    }

    // go on with the next level
    if(current_level < m_L)
    {
        // iterate again with the resulting clusters
        const std::vector<NodeId> &children_ids = m_nodes[parent_id].children;

        // 对每一个新的聚类中心，递归的进行上述操作，直到达到预先设置的层数
        for(unsigned int i = 0; i < clusters.size(); ++i)
        {
            NodeId id = children_ids[i];

            std::vector<cv::Mat> child_features;
            child_features.reserve(groups[i].size());

            std::vector<unsigned int>::const_iterator vit;
            for(vit = groups[i].begin(); vit != groups[i].end(); ++vit)
            {
                child_features.push_back(descriptors[*vit]);
            }

            if(child_features.size() > 1)
            {
                HKmeansStep(id, child_features, current_level + 1);
            }
        }
    }
}

// --------------------------------------------------------------------------


void Vocabulary::initiateClusters
  (const std::vector<cv::Mat> &descriptors,
   std::vector<cv::Mat> &clusters) const
{
  initiateClustersKMpp(descriptors, clusters);
}

// --------------------------------------------------------------------------


void Vocabulary::initiateClustersKMpp(
  const std::vector<cv::Mat> &pfeatures,
    std::vector<cv::Mat> &clusters) const
{
  // Implements kmeans++ seeding algorithm
  // Algorithm:
  // 1. Choose one center uniformly at random from among the data points.
  // 2. For each data point x, compute D(x), the distance between x and the nearest
  //    center that has already been chosen.
  // 3. Add one new data point as a center. Each point x is chosen with probability
  //    proportional to D(x)^2.
  // 4. Repeat Steps 2 and 3 until k centers have been chosen.
  // 5. Now that the initial centers have been chosen, proceed using standard k-means
  //    clustering.


//  DUtils::Random::SeedRandOnce();

  clusters.resize(0);
  clusters.reserve(m_k);
  std::vector<double> min_dists(pfeatures.size(), std::numeric_limits<double>::max());

  // 1.

  int ifeature = rand()% pfeatures.size();//DUtils::Random::RandomInt(0, pfeatures.size()-1);

  // create first cluster
  clusters.push_back(pfeatures[ifeature]);

  // compute the initial distances
   std::vector<double>::iterator dit;
  dit = min_dists.begin();
  for(auto fit = pfeatures.begin(); fit != pfeatures.end(); ++fit, ++dit)
  {
    *dit = DescManip::distance((*fit), clusters.back());
  }

  while((int)clusters.size() < m_k)
  {
    // 2.
    dit = min_dists.begin();
    for(auto  fit = pfeatures.begin(); fit != pfeatures.end(); ++fit, ++dit)
    {
      if(*dit > 0)
      {
        double dist = DescManip::distance((*fit), clusters.back());
        if(dist < *dit) *dit = dist;
      }
    }

    // 3.
    double dist_sum = std::accumulate(min_dists.begin(), min_dists.end(), 0.0);

    if(dist_sum > 0)
    {
      double cut_d;
      do
      {

        cut_d = (double(rand())/ double(RAND_MAX))* dist_sum;
      } while(cut_d == 0.0);

      double d_up_now = 0;
      for(dit = min_dists.begin(); dit != min_dists.end(); ++dit)
      {
        d_up_now += *dit;
        if(d_up_now >= cut_d) break;
      }

      if(dit == min_dists.end())
        ifeature = pfeatures.size()-1;
      else
        ifeature = dit - min_dists.begin();


      clusters.push_back(pfeatures[ifeature]);
    } // if dist_sum > 0
    else
      break;

  } // while(used_clusters < m_k)

}

// --------------------------------------------------------------------------


void Vocabulary::createWords()
{
  m_words.resize(0);

  if(!m_nodes.empty())
  {
    m_words.reserve( (int)pow((double)m_k, (double)m_L) );


    auto  nit = m_nodes.begin(); // ignore root
    for(++nit; nit != m_nodes.end(); ++nit)
    {
        // 在词袋树中，树的所有叶子节点构成最终的单词
      if(nit->isLeaf())
      {
        // 注意，m_words 的大小会随着单词数的添加而增加，所以单词的 ID 也会自动增加
        nit->word_id = m_words.size();
        m_words.push_back( &(*nit) );
      }
    }
  }
}

// --------------------------------------------------------------------------


/**
 * @brief 这里便是用 TF-IDF 方法根据训练词袋所用的描述子，给每个单词赋予权重
 */
void Vocabulary::setNodeWeights
  (const std::vector<std::vector<cv::Mat> > &training_features)
{
  const unsigned int NWords = m_words.size();
  const unsigned int NDocs = training_features.size();

  if(m_weighting == TF || m_weighting == BINARY)
  {
    // idf part must be 1 always
    for(unsigned int i = 0; i < NWords; i++)
      m_words[i]->weight = 1;
  }
  else if(m_weighting == IDF || m_weighting == TF_IDF)
  {
    // IDF and TF-IDF: we calculte the idf path now

    // Note: this actually calculates the idf part of the tf-idf score.
    // The complete tf-idf score is calculated in ::transform

    std::vector<unsigned int> Ni(NWords, 0);
    std::vector<bool> counted(NWords, false);


    for(auto mit = training_features.begin(); mit != training_features.end(); ++mit)
    {
      fill(counted.begin(), counted.end(), false);

      for(auto fit = mit->begin(); fit < mit->end(); ++fit)
      {
        // 找到当前描述子对应的单词 ID
        WordId word_id;
        transform(*fit, word_id);

        // 累加训练图像中该单词出现的次数，注意: 对于单张图像，只统计一次 (不清楚为什么)
        if(!counted[word_id])
        {
          Ni[word_id]++;
          counted[word_id] = true;
        }
      }
    }

    // set ln(N/Ni)
    for(unsigned int i = 0; i < NWords; i++)
    {
      if(Ni[i] > 0)
      {
        // 这里的 NDocs 指的是图像的数量，并不是所有描述子的数量
        m_words[i]->weight = log((double)NDocs / (double)Ni[i]);
      }// else // This cannot occur if using kmeans++
    }

  }

}

// --------------------------------------------------------------------------






// --------------------------------------------------------------------------


float Vocabulary::getEffectiveLevels() const
{
  long sum = 0;
   for(auto wit = m_words.begin(); wit != m_words.end(); ++wit)
  {
    const Node *p = *wit;

    for(; p->id != 0; sum++) p = &m_nodes[p->parent];
  }

  return (float)((double)sum / (double)m_words.size());
}

// --------------------------------------------------------------------------


cv::Mat Vocabulary::getWord(WordId wid) const
{
  return m_words[wid]->descriptor;
}

// --------------------------------------------------------------------------


WordValue Vocabulary::getWordWeight(WordId wid) const
{
  return m_words[wid]->weight;
}

// --------------------------------------------------------------------------


WordId Vocabulary::transform
  (const cv::Mat& feature) const
{
  if(empty())
  {
    return 0;
  }

  WordId wid;
  transform(feature, wid);
  return wid;
}

// --------------------------------------------------------------------------

void Vocabulary::transform(
        const cv::Mat& features, BowVector &v) const
{
    //    std::vector<cv::Mat> vf(features.rows);
    //    for(int r=0;r<features.rows;r++) vf[r]=features.rowRange(r,r+1);
    //    transform(vf,v);



    v.clear();

    if(empty())
    {
        return;
    }

    // normalize
    LNorm norm;
    bool must = m_scoring_object->mustNormalize(norm);


    if(m_weighting == TF || m_weighting == TF_IDF)
    {
        for(int r=0;r<features.rows;r++)
        {
            WordId id;
            WordValue w;
            // w is the idf value if TF_IDF, 1 if TF
            transform(features.row(r), id, w);
            // not stopped
            if(w > 0)  v.addWeight(id, w);
        }

        if(!v.empty() && !must)
        {
            // unnecessary when normalizing
            const double nd = v.size();
            for(BowVector::iterator vit = v.begin(); vit != v.end(); vit++)
                vit->second /= nd;
        }

    }
    else // IDF || BINARY
    {
        for(int r=0;r<features.rows;r++)
        {
            WordId id;
            WordValue w;
            // w is idf if IDF, or 1 if BINARY

            transform(features.row(r), id, w);

            // not stopped
            if(w > 0) v.addIfNotExist(id, w);

        } // if add_features
    } // if m_weighting == ...

    if(must) v.normalize(norm);

}



void Vocabulary::transform(
  const std::vector<cv::Mat>& features, BowVector &v) const
{
  v.clear();

  if(empty())
  {
    return;
  }

  // normalize
  LNorm norm;
  bool must = m_scoring_object->mustNormalize(norm);


  if(m_weighting == TF || m_weighting == TF_IDF)
  {
    for(auto fit = features.begin(); fit < features.end(); ++fit)
    {
      WordId id;
      WordValue w;
      // w is the idf value if TF_IDF, 1 if TF

      transform(*fit, id, w);

      // not stopped
      if(w > 0) v.addWeight(id, w);
    }

    if(!v.empty() && !must)
    {
      // unnecessary when normalizing
      const double nd = v.size();
      for(BowVector::iterator vit = v.begin(); vit != v.end(); vit++)
        vit->second /= nd;
    }

  }
  else // IDF || BINARY
  {
    for(auto fit = features.begin(); fit < features.end(); ++fit)
    {
      WordId id;
      WordValue w;
      // w is idf if IDF, or 1 if BINARY

      transform(*fit, id, w);

      // not stopped
      if(w > 0) v.addIfNotExist(id, w);

    } // if add_features
  } // if m_weighting == ...

  if(must) v.normalize(norm);
}

// --------------------------------------------------------------------------


void Vocabulary::transform
  (const cv::Mat &feature, WordId &id) const
{
  WordValue weight;
  transform(feature, id, weight);
}

// --------------------------------------------------------------------------


void Vocabulary::transform(const cv::Mat &feature,
  WordId &word_id, WordValue &weight, NodeId *nid, int levelsup) const
{
  // propagate the feature down the tree


  // level at which the node must be stored in nid, if given
  const int nid_level = m_L - levelsup;
  if(nid_level <= 0 && nid != NULL) *nid = 0; // root

  NodeId final_id = 0; // root
  int current_level = 0;

  do
  {
    ++current_level;
    auto const  &nodes = m_nodes[final_id].children;
    double best_d = std::numeric_limits<double>::max();
//    DescManip::distance(feature, m_nodes[final_id].descriptor);

    for(const auto  &id:nodes)
    {
      double d = DescManip::distance(feature, m_nodes[id].descriptor);
      if(d < best_d)
      {
        best_d = d;
        final_id = id;
      }
    }

    if(nid != NULL && current_level == nid_level)
      *nid = final_id;

  } while( !m_nodes[final_id].isLeaf() );

  // turn node id into word id
  word_id = m_nodes[final_id].word_id;
  weight = m_nodes[final_id].weight;
}



void Vocabulary::transform(const cv::Mat &feature,
  WordId &word_id, WordValue &weight ) const
{
  // propagate the feature down the tree
  // level at which the node must be stored in nid, if given

  NodeId final_id = 0; // root
//maximum speed by computing here distance and avoid calling to DescManip::distance

  //binary descriptor
 // int ntimes=0;
  if (feature.type()==CV_8U){
      do
      {
          auto const  &nodes = m_nodes[final_id].children;
          uint64_t best_d = std::numeric_limits<uint64_t>::max();

           for(const auto  &id:nodes)
          {
              //compute distance
              uint64_t dist= DescManip::distance_8uc1(feature, m_nodes[id].descriptor);
              if(dist < best_d)
              {
                  best_d = dist;
                  final_id = id;
              }
          }
      } while( !m_nodes[final_id].isLeaf() );
   }
  else
  {
	  do
	  {
		  auto const  &nodes = m_nodes[final_id].children;
		  uint64_t best_d = std::numeric_limits<uint64_t>::max();

		  for (const auto &id : nodes)
		  {
			  // compute distance
			  uint64_t dist = DescManip::distance(feature, m_nodes[id].descriptor);
			  if (dist < best_d)
			  {
				  best_d = dist;
				  final_id = id;
			  }
		  }
	  } while (!m_nodes[final_id].isLeaf());
  }

  // turn node id into word id
  word_id = m_nodes[final_id].word_id;
  weight = m_nodes[final_id].weight;
}
// --------------------------------------------------------------------------

NodeId Vocabulary::getParentNode
  (WordId wid, int levelsup) const
{
  NodeId ret = m_words[wid]->id; // node id
  while(levelsup > 0 && ret != 0) // ret == 0 --> root
  {
    --levelsup;
    ret = m_nodes[ret].parent;
  }
  return ret;
}

// --------------------------------------------------------------------------


void Vocabulary::getWordsFromNode
  (NodeId nid, std::vector<WordId> &words) const
{
  words.clear();

  if(m_nodes[nid].isLeaf())
  {
    words.push_back(m_nodes[nid].word_id);
  }
  else
  {
    words.reserve(m_k); // ^1, ^2, ...

    std::vector<NodeId> parents;
    parents.push_back(nid);

    while(!parents.empty())
    {
      NodeId parentid = parents.back();
      parents.pop_back();

      const std::vector<NodeId> &child_ids = m_nodes[parentid].children;
      std::vector<NodeId>::const_iterator cit;

      for(cit = child_ids.begin(); cit != child_ids.end(); ++cit)
      {
        const Node &child_node = m_nodes[*cit];

        if(child_node.isLeaf())
          words.push_back(child_node.word_id);
        else
          parents.push_back(*cit);

      } // for each child
    } // while !parents.empty
  }
}

// --------------------------------------------------------------------------


int Vocabulary::stopWords(double minWeight)
{
  int c = 0;
   for(auto wit = m_words.begin(); wit != m_words.end(); ++wit)
  {
    if((*wit)->weight < minWeight)
    {
      ++c;
      (*wit)->weight = 0;
    }
  }
  return c;
}

// --------------------------------------------------------------------------


void Vocabulary::load(const std::string &filename)
{
    //check first if it is a binary file
    std::ifstream ifile(filename,std::ios::binary);
    if (!ifile)
    {
        throw std::runtime_error("Vocabulary::load Could not open file :"+filename+" for reading");
    }

    cv::FileStorage fs(filename.c_str(), cv::FileStorage::READ);
    if(!fs.isOpened()) throw std::string("Could not open file ") + filename;
    load(fs);
}


void Vocabulary::save(cv::FileStorage &f,
  const std::string &name) const
{

  f << name << "{";

  f << "k" << m_k;
  f << "L" << m_L;
  f << "scoringType" << m_scoring;
  f << "weightingType" << m_weighting;

  // tree
  f << "nodes" << "[";
  std::vector<NodeId> parents, children;
  std::vector<NodeId>::const_iterator pit;

  parents.push_back(0); // root

  while(!parents.empty())
  {
    NodeId pid = parents.back();
    parents.pop_back();

    const Node& parent = m_nodes[pid];
    children = parent.children;

    for(pit = children.begin(); pit != children.end(); pit++)
    {
      const Node& child = m_nodes[*pit];
      std::cout<<m_nodes[*pit].id<<" ";

      // save node data
      f << "{:";
      f << "nodeId" << (int)child.id;
      f << "parentId" << (int)pid;
      f << "weight" << (double)child.weight;
      f << "descriptor" << DescManip::toString(child.descriptor);
      f << "}";

      // add to parent list
      if(!child.isLeaf())
      {
        parents.push_back(*pit);
      }
    }
  }
  std::cout<<"\n";

  f << "]"; // nodes

  // words
  f << "words" << "[";

   for(auto wit = m_words.begin(); wit != m_words.end(); wit++)
  {
    WordId id = wit - m_words.begin();
    f << "{:";
    f << "wordId" << (int)id;
    f << "nodeId" << (int)(*wit)->id;
    f << "}";
  }

  f << "]"; // words

  f << "}";

}

void Vocabulary:: load_fromtxt(const std::string &filename){

    std::ifstream ifile(filename);
    if(!ifile)throw std::runtime_error("Vocabulary:: load_fromtxt  Could not open file for reading:"+filename);
    int n1, n2;
    {
    std::string str;
    getline(ifile,str);
    std::stringstream ss(str);
    ss>>m_k>>m_L>>n1>>n2;
    }
    if(m_k<0 || m_k>20 || m_L<1 || m_L>10 || n1<0 || n1>5 || n2<0 || n2>3)
         throw std::runtime_error( "Vocabulary loading failure: This is not a correct text file!" );

    m_scoring = (ScoringType)n1;
    m_weighting = (WeightingType)n2;
    createScoringObject();
    // nodes
       int expected_nodes =
       (int)((pow((double)m_k, (double)m_L + 1) - 1)/(m_k - 1));
       m_nodes.reserve(expected_nodes);

       m_words.reserve(pow((double)m_k, (double)m_L + 1));

       m_nodes.resize(1);
       m_nodes[0].id = 0;

       int counter=0;
       while(!ifile.eof()){
           std::string snode;
           getline(ifile,snode);
           if (counter++%100==0)std::cerr<<".";
          // std::cout<<snode<<std::endl;
           if (snode.size()==0)break;
           std::stringstream ssnode(snode);

           int nid = m_nodes.size();
           m_nodes.resize(m_nodes.size()+1);
           m_nodes[nid].id = nid;

           int pid ;
           ssnode >> pid;
           m_nodes[nid].parent = pid;
           m_nodes[pid].children.push_back(nid);

           int nIsLeaf;
           ssnode >> nIsLeaf;

           //read until the end and add to data
           std::vector<float> data;data.reserve(100);
           float d;
           while( ssnode>>d) data.push_back(d);
           //the weight is the last
           m_nodes[nid].weight=data.back();
           data.pop_back();//remove
           //the rest, to the descriptor
           m_nodes[nid].descriptor.create(1,data.size(),CV_8UC1);
           auto ptr=m_nodes[nid].descriptor.ptr<uchar>(0);
           for(auto d:data) *ptr++=d;


           if(nIsLeaf>0)
           {
               int wid = m_words.size();
               m_words.resize(wid+1);

               m_nodes[nid].word_id = wid;
               m_words[wid] = &m_nodes[nid];
           }
           else
           {
               m_nodes[nid].children.reserve(m_k);
           }
       }
}
// --------------------------------------------------------------------------

void Vocabulary::load(const cv::FileStorage &fs,
  const std::string &name)
{
  m_words.clear();
  m_nodes.clear();

  cv::FileNode fvoc = fs[name];

  m_k = (int)fvoc["k"];
  m_L = (int)fvoc["L"];
  m_scoring = (ScoringType)((int)fvoc["scoringType"]);
  m_weighting = (WeightingType)((int)fvoc["weightingType"]);

  createScoringObject();

  // nodes
  cv::FileNode fn = fvoc["nodes"];

  m_nodes.resize(fn.size() + 1); // +1 to include root
  m_nodes[0].id = 0;

  for(unsigned int i = 0; i < fn.size(); ++i)
  {
    NodeId nid = (int)fn[i]["nodeId"];
    NodeId pid = (int)fn[i]["parentId"];
    WordValue weight = (WordValue)fn[i]["weight"];
    std::string d = (std::string)fn[i]["descriptor"];

    m_nodes[nid].id = nid;
    m_nodes[nid].parent = pid;
    m_nodes[nid].weight = weight;
    m_nodes[pid].children.push_back(nid);

    DescManip::fromString(m_nodes[nid].descriptor, d);
  }

  // words
  fn = fvoc["words"];

  m_words.resize(fn.size());

  for(unsigned int i = 0; i < fn.size(); ++i)
  {
    NodeId wid = (int)fn[i]["wordId"];
    NodeId nid = (int)fn[i]["nodeId"];

    m_nodes[nid].word_id = wid;
    m_words[wid] = &m_nodes[nid];
  }
}

// --------------------------------------------------------------------------

/**
 * Writes printable information of the vocabulary
 * @param os stream to write to
 * @param voc
 */

std::ostream& operator<<(std::ostream &os,
  const Vocabulary &voc)
{
  os << "Vocabulary: k = " << voc.getBranchingFactor()
    << ", L = " << voc.getDepthLevels()
    << ", Weighting = ";

  switch(voc.getWeightingType())
  {
    case TF_IDF: os << "tf-idf"; break;
    case TF: os << "tf"; break;
    case IDF: os << "idf"; break;
    case BINARY: os << "binary"; break;
  }

  os << ", Scoring = ";
  switch(voc.getScoringType())
  {
    case L1_NORM: os << "L1-norm"; break;
    case L2_NORM: os << "L2-norm"; break;
    case CHI_SQUARE: os << "Chi square distance"; break;
    case KL: os << "KL-divergence"; break;
    case BHATTACHARYYA: os << "Bhattacharyya coefficient"; break;
    case DOT_PRODUCT: os << "Dot product"; break;
  }

  os << ", Number of words = " << voc.size();

  return os;
}
/**
 * @brief Vocabulary::clear
 */
void Vocabulary::clear(){
    delete m_scoring_object;
    m_scoring_object=0;
    m_nodes.clear();
    m_words.clear();

}
int Vocabulary::getDescritorSize()const
{
    if (m_words.size()==0)return -1;
    else return m_words[0]->descriptor.cols;
}
int Vocabulary::getDescritorType()const{

    if (m_words.size()==0)return -1;
    else return m_words[0]->descriptor.type();
}


}
