// Copyright 2024 Tushentsova Karina
#pragma once

#include <list>
#include <random>
#include <thread>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

class markingImageStl : public ppc::core::Task {
 public:
  bool run() override;
  bool validation() override;
  bool pre_processing() override;
  bool post_processing() override;
  explicit markingImageStl(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}

 private:
  uint32_t height{}, width{};
  uint32_t countThreads;
  std::vector<std::vector<uint32_t>> sourse = {};
  std::vector<std::vector<uint32_t>> destination = {};
  void markingImage();
};