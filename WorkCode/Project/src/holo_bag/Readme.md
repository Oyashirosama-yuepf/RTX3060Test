# holo_bag
holo_bag is a storage tool for holomatic auto pilot system.

## Install
>
### download the holo_bag repo to a holo_builder workspace
>
> git clone ssh://git@out.holomatic.ai:5005/win/holo_bag.git
>

### make sure the build package is newest holo_dragonglass/dragonglass-master


### make install


### first you should build holo_3rdparty(master) holo_base(dragonglass-develop) holo_cmw(dragonglass-develop)


### then make sure the holo_bag branch is master
> 
> holo build holo_bag
>
> holo build holo_bag/cmw_app
>


## Quick Tutorial


### holobag completion
>
> sudo cp script/holobag_complete.bash /etc/bash_completion.d/
> 
> then you can make an alias to your .bashrc named holobag
>
> like :
alias holobag='source ~/holo_ws/output/native/relwithdebinfo/target/setenv.bash &&  ~/holo_ws/output/native/relwithdebinfo/target/bin/opendds/holobag'
>
>

### PreCondition

You need to run the script in your opendds target before use the following exe 
>
> sh start_dcps_info_repo.sh
>

### record
>
> holobag record (optional) -O <output_name>
>

### play
>
> holobag play -i <bag_uri> (optional) -s <skip_time> -r <rate>
>
### info
>
> holobag info <bag_uri>
> 
### filter
>
> holobag filter -i <input_file> -o <output_file_name> -s <start_time> -e <end_time>
>


### help
>
> holobag record -h
>
> holobag play -h
>
> holobag info -h
>
> holobag filter -h
>

### tips

you can install a sqlite browser to analyse the message you get.
>
>sudo apt-get install sqlitebrowser
>


## Note

### 1. holobag record 现阶段只能录存储在app_config 中的 record_topics.yaml中的type和topics.
#### a.如果想要添加的topic的type已经在yaml中存在，可以直接在其下方的topic_names中添加
#### b.如果想要添加的topic是一个新的type，则需要在代码中的holo_record以及holo_replay中添加相应处理###
### 2. holobag record存储的数据的序列化格式暂时固定为 host 4Byte
### 3. 现阶段存储的单帧数据最大为200000Byte，即200kB,如果新topic超过该数值，请联系**liwenchao@holomatic.com** 
### 4.  holo record可以在任意目录启动，录取的bag会存储在启动目录，名称如果没有-O输入，则固定为系统时间。

## Bug Report
Report bug to **liwenchao@holomatic.com**