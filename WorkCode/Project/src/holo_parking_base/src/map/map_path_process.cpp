/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_path_process.cpp
 * @brief The impl of map path process
 * @author lizhao(lizhao@holomaitc.com)
 * @date 2022-02-11
 */
#include <holo/log/hololog.h>
#include <holo/parking/map/map_path_process.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
using namespace std;
namespace holo
{
namespace parking
{
namespace map
{
bool_t MapPathProcess::SaveParkingPath2File(ParkingPath& parking_path, std::string const file_path)
{
    std::ofstream os(file_path, ios_base::out | ios_base::binary);
    size_t        parking_path_size = parking_path.GetSerializedSize();
    uint8_t*      buffer            = new uint8_t[parking_path_size];

    holo::serialization::Serializer<> ser(buffer, parking_path_size);

    ser << parking_path;
    os.write(reinterpret_cast<char*>(&parking_path_size), sizeof(parking_path_size));
    os.write(reinterpret_cast<char*>(buffer), parking_path_size);
    os.close();

    delete[] buffer;

    return true;
}

bool_t MapPathProcess::LoadFile2ParkingPath(std::string const file_path, ParkingPath& parking_path)
{
    std::ifstream is(file_path, ios_base::in | ios_base::binary);
    size_t        path_size = 0;

    LOG(INFO) << "LoadFile2ParkingPath, file = " << file_path;

    struct stat info;
    stat(file_path.c_str(), &info);
    size_t size = info.st_size;

    if (size <= 4)
    {
        LOG(WARNING) << "File size is " << size << " ,format is error.";
        return false;
    }

    if (is)
    {
        is.read(reinterpret_cast<char*>(&path_size), sizeof(path_size));
        if (path_size <= 0)
        {
            LOG(ERROR) << "LoadFile2ParkingPath error, path_size = " << path_size;
            return false;
        }
        uint8_t* rcv_buffer = new uint8_t[path_size];

        is.read(reinterpret_cast<char*>(rcv_buffer), path_size);
        holo::serialization::Deserializer<> des(rcv_buffer, path_size);
        des >> parking_path;

        is.close();
        delete[] rcv_buffer;

        return true;
    }
    else
    {
        LOG(ERROR) << "LoadFile2ParkingPath error, Cannot open file " << file_path;
        is.close();

        return false;
    }
}
}  // namespace map
}  // namespace parking
}  // namespace holo
