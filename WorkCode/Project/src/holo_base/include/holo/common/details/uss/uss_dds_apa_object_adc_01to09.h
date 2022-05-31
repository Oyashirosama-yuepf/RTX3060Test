#ifndef  HOLO_COMMON_DETAILS_USS_DDS_APA_OBJECT_ADC_01TO09_H_
#define HOLO_COMMON_DETAILS_USS_DDS_APA_OBJECT_ADC_01TO09_H_
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>



namespace holo
{
namespace common
{
namespace details
{
static const unsigned int ARRAY_ADC_01TO09_LENGTH = 20;
//////////////////////////////////get/////////////////////////////////////////////////////////
/////////////////////////USSDDSMapObj///////////////////////////////////////////
class USSDDSMapObj
{
public:
   //APA_ADC_01
   USSDDSMapObj()
   {
		this->dds_MapObjHei = 0;
		this->dds_MapObjHeiProblty= 0;
		this->dds_MapObjP1X= 0;
		this->dds_MapObjP1Y= 0;
		this->dds_MapObjP2X= 0;
		this->dds_MapObjP2Y= 0;
		this->dds_MapObjProblty= 0;
		this->dds_MapObjTyp= 0;
   }
   ~USSDDSMapObj()
   {
		this->dds_MapObjHei= 0;
		this->dds_MapObjHeiProblty= 0;
		this->dds_MapObjP1X= 0;
		this->dds_MapObjP1Y= 0;
		this->dds_MapObjP2X= 0;
		this->dds_MapObjP2Y= 0;
		this->dds_MapObjProblty= 0;
		this->dds_MapObjTyp= 0;
   }
   USSDDSMapObj (const USSDDSMapObj & rhs) = delete; 
   USSDDSMapObj & operator=(const USSDDSMapObj & rhs) = delete; 
   //////////////////////GetSerializedSize///////////////////////////
   template <size_t ALIGN = 4U>
	size_t GetSerializedSize() const noexcept
    {
        return sizeof(USSDDSMapObj);
    }
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer <<  this->dds_MapObjHei <<  this->dds_MapObjHeiProblty <<  this->dds_MapObjP1X <<  this->dds_MapObjP1Y 
		<<  this->dds_MapObjP2X<< this->dds_MapObjP2Y  <<  this->dds_MapObjProblty << this->dds_MapObjTyp;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >>this->dds_MapObjHei >>  this->dds_MapObjHeiProblty >>  this->dds_MapObjP1X >>  this->dds_MapObjP1Y 
		>>  this->dds_MapObjP2X>> this->dds_MapObjP2Y  >>  this->dds_MapObjProblty >> this->dds_MapObjTyp;
    }
	////////////////////get////////////////////////////////
	uint8_t GetDdsMapobjhei() 
	{
		return this->dds_MapObjHei;
	}
	float32_t GetDdsMapobjheiproblty() 
	{
		return this->dds_MapObjHeiProblty; 
	}
	int16_t GetDdsMapobjp1x() 
	{
		return this->dds_MapObjP1X;
	}
	int16_t GetDdsMapobjp1y() 
	{
		return this->dds_MapObjP1Y;
	}
	int16_t GetDdsMapobjp2x() 
	{
		return this->dds_MapObjP2X;
	}
	int16_t GetDdsMapobjp2y() 
	{
		return this->dds_MapObjP2Y;
	}
	float32_t GetDdsMapobjproblty() 
	{
		return this->dds_MapObjProblty;
	}
	uint8_t GetDdsMapobjtyp() 
	{
		return this->dds_MapObjTyp;
	}
	/////////////////////////////////set////////////////////////
	void SetDdsMapObjhei(const  uint8_t value) 
	{	
		this->dds_MapObjHei = value;
	}
	void SetDdsMapObjheiproblty(const float32_t value) 
	{	
		this->dds_MapObjHeiProblty = value; 
	}
	void SetDdsMapObjp1x(const int16_t value) 
	{	
		this->dds_MapObjP1X = value;
	}
	void SetDdsMapObjp1y(const int16_t value) 
	{	
		this->dds_MapObjP1Y = value;
	}
	void SetDdsMapObjp2x(const int16_t value) 
	{		
		this->dds_MapObjP2X = value;
	}
	void SetDdsMapObjp2y(const int16_t value) 
	{	
		this->dds_MapObjP2Y= value;
	}	
	void SetDdsMapObjproblty(const float32_t value)  
	{
		this->dds_MapObjProblty = value;
	}
	void  SetDdsMapObjtyp(const uint8_t value) 
	{		
		this->dds_MapObjTyp = value;
	}
public:
	holo::uint8_t dds_MapObjHei;
	holo::float32_t dds_MapObjHeiProblty;
	holo::int16_t dds_MapObjP1X;
	holo:: int16_t dds_MapObjP1Y;
	holo::int16_t dds_MapObjP2X;
	holo::int16_t dds_MapObjP2Y;
	holo::float32_t dds_MapObjProblty;
	holo::uint8_t dds_MapObjTyp;
};//USSDDSMapObj
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////DDSUSSApaObjectAdc01to09//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
class DDSUSSApaObjectAdc01to09
{
public:
        /////////////////////construction//////////////
		DDSUSSApaObjectAdc01to09()
		{
		}
		~DDSUSSApaObjectAdc01to09()
	    {
		}
	    DDSUSSApaObjectAdc01to09 (const DDSUSSApaObjectAdc01to09 & rhs) = delete; 
		DDSUSSApaObjectAdc01to09 & operator=(const DDSUSSApaObjectAdc01to09 & rhs) = delete; 

		//////////////////////////GetSerializedSize///////////////////////////////
		template <size_t ALIGN = 4U>
		size_t GetSerializedSize() const noexcept
		{
		 return timestamp_.GetSerializedSize<ALIGN>() +
				holo::serialization::AlignedSize<ALIGN>(sizeof(USSDDSMapObj) * ARRAY_ADC_01TO09_LENGTH);
		}

		template <typename S>
		void Serialize(S& serializer) const
		{
            serializer <<  this->timestamp_;   
			for (size_t index = 0U; index <  ARRAY_ADC_01TO09_LENGTH; index++)
			{
				serializer <<  this->obj[index];
			}
			serializer << holo::serialization::align;
		}

		template <typename D>
		void Deserialize(D& deserializer)
		{
			deserializer >>  this->timestamp_ ;
			for (size_t index = 0U; index <ARRAY_ADC_01TO09_LENGTH; index++)
			{
				deserializer >>  this->obj[index];
			}
			deserializer >> holo::serialization::align;
		}
		 ////////////////////////SetTimestamp/////////////////////////////////////////
		void SetTimestamp(Timestamp const timestamp)
		{
			this->timestamp_ = timestamp;
		}
		//////////////////////////////////////////////
		Timestamp GetTimestamp() const noexcept
		{
			return  this->timestamp_;
		}

private:
	holo::common::Timestamp timestamp_;  
public:
    USSDDSMapObj   obj[ARRAY_ADC_01TO09_LENGTH];

};//DDSUSSApaObjectAdc01to09
}  // namespace details
}  // namespace common
}  // namespace holo
#endif//HOLO_COMMON_DETAILS_USS_DDS_APA_OBJECT_ADC_01TO09_H_
