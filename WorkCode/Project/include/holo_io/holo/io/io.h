/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file io.h
 * @brief 
 * @author
 * @date
 */

#ifndef HOLO_IO_H_
#define HOLO_IO_H_

#include <fstream>
#include <iostream>
#include <vector>

#include <holo/io/utils/skip.h>

namespace holo_io
{

typedef std::pair<std::string, std::ofstream> OutputTopicFn;
typedef std::vector<OutputTopicFn> OutputTopicFnList;

template <typename INPUT>
void ToStream(std::ostream& os, const INPUT& input);

template <typename OUTPUT>
void FromStream(std::istream& is, OUTPUT& output);

template <typename INPUT>
void Save(const std::vector<INPUT>& data, const std::string& fn);

template <typename OUTPUT>
std::vector<OUTPUT> Load(const std::string& fn);

}

#endif