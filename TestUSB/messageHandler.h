
#pragma once
#include"stdafx.h"
#include<unordered_map>
#include<set>
#include<string>
#include<vector>
#include"Serial.h"
#include<shared_mutex>
#include<atomic>
#include<tuple>
#include <functional>
class messageHandler {
private:
    std::vector<std::vector<int>> colorMatrixRed;
    std::vector<std::vector<int>> colorMatrixGreen;
    std::vector<std::vector<int>> colorMatrixBlue;
    int colorMatrixHeight;
    int colorMatrixWidth;
	unsigned char* data;
    int dataLength;
    
    struct TupleHash {
        size_t operator()(const std::tuple<int, int, int>& key) const {
            size_t seed = 0;
            auto hash_combine = [&seed](int value) {
                std::hash<int> hasher;
                seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                };
            hash_combine(std::get<0>(key));
            hash_combine(std::get<1>(key));
            hash_combine(std::get<2>(key));
            return seed;
        }
    };

    const std::unordered_map<std::tuple<int, int, int>, std::string, TupleHash> exp_image_dict = {
        {std::make_tuple(41, 65, 93), "A1"},   {std::make_tuple(87, 152, 13), "A2"},
        {std::make_tuple(213, 109, 81), "A3"}, {std::make_tuple(23, 222, 55), "A4"},
        {std::make_tuple(69, 203, 71), "A5"},  {std::make_tuple(147, 253, 55), "A6"},
        {std::make_tuple(77, 19, 35), "A7"},   {std::make_tuple(159, 109, 79), "A8"},
        {std::make_tuple(87, 217, 111), "B1"}, {std::make_tuple(149, 95, 154), "B2"},
        {std::make_tuple(97, 233, 9), "B3"},   {std::make_tuple(159, 27, 222), "B4"},
        {std::make_tuple(152, 173, 186), "B5"}, {std::make_tuple(192, 185, 149), "B6"},
        {std::make_tuple(158, 45, 23), "B7"},  {std::make_tuple(197, 158, 219), "B8"},
        {std::make_tuple(127, 144, 79), "C1"}, {std::make_tuple(242, 41, 155), "C2"},
        {std::make_tuple(69, 67, 213), "D1"},  {std::make_tuple(105, 25, 130), "D2"},
        {std::make_tuple(17, 39, 170), "D3"},  {std::make_tuple(97, 103, 203), "D4"},
        {std::make_tuple(113, 25, 77), "D5"},  {std::make_tuple(21, 21, 140), "D6"},
        {std::make_tuple(155, 179, 166), "D7"}, {std::make_tuple(55, 181, 134), "D8"},
        {std::make_tuple(61, 33, 27), "E1"},   {std::make_tuple(51, 91, 95), "E2"},
        {std::make_tuple(143, 227, 63), "E3"}, {std::make_tuple(216, 67, 226), "E4"},
        {std::make_tuple(202, 181, 245), "E5"}, {std::make_tuple(99, 11, 183), "E6"},
        {std::make_tuple(75, 119, 224), "E7"}, {std::make_tuple(182, 19, 85), "E8"}
    };

    const std::vector<std::vector<std::string>> exp_list = {
    {"A1", "A2", "A3", "A4", "A5"},
    {"A6", "A7", "A8", "B1", "B2"},
    {"B3", "B4", "B5", "B6", "B7"},
    {"B8", "C1", "C2", "D1", "D2"},
    {"D3", "D4", "D5", "D6", "D7"},
    {"D8", "E1", "E2", "E3", "E4"},
    {"E5", "E6", "E7", "E8"}
    };
    CSerial* serialPort;
    void writeThread();
    void readThread();
    std::atomic<int> start;
    std::shared_mutex mtx;
    std::thread read_Thread;
    std::thread write_Thread;
    char sendMessage[9] = { 40,0,0,0,0,0,0,0,41 };
public:
    messageHandler();
    ~messageHandler();
    void handle(unsigned char* data, int dataLength);
    std::set<std::string> transferToMaiSerial(unsigned char*);
};
