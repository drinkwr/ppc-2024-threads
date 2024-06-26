// Copyright 2024 Troitskiy Alexandr
#include <gtest/gtest.h>
#include <omp.h>

#include <cmath>

#include "core/perf/include/perf.hpp"
#include "omp/troitskiy_a_int_trapezoid_omp/include/ops_omp.hpp"

TEST(openmp_troitskiy_a_int_trapezoid, test_pipeline_run) {
  double a1 = 0.0;
  double b1 = 3.14159265358979323846;
  double a2 = 0.0;
  double b2 = 3.14159265358979323846;

  int n1 = 1000;
  int n2 = 1000;

  double res = 2 * 3.14159265358979323846;

  auto sin_cos = [](double x, double y) { return sin(x) + cos(y); };

  // Create data
  std::vector<double> in = {a1, b1, a2, b2};
  std::vector<double> out(1, res);
  std::vector<int> n = {n1, n2};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(n.data()));
  taskDataSeq->inputs_count.emplace_back(n.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  auto testTaskOMP = std::make_shared<troitskiy_a_omp_integral_trapezoid::TestOMPTaskParalleltroitskiyIntegralTrapezoid>(
      taskDataSeq, sin_cos);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  perfAttr->current_timer = [&] { return omp_get_wtime(); };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskOMP);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_NEAR(res, out[0], 0.02);
}

TEST(openmp_troitskiy_a_int_trapezoid, test_task_run) {
  double a1 = 0.0;
  double b1 = 3.14159265358979323846;
  double a2 = 0.0;
  double b2 = 3.14159265358979323846;

  int n1 = 1000;
  int n2 = 1000;

  double res = 2 * 3.14159265358979323846;

  auto sin_cos = [](double x, double y) { return sin(x) + cos(y); };

  // Create data
  std::vector<double> in = {a1, b1, a2, b2};
  std::vector<double> out(1, res);
  std::vector<int> n = {n1, n2};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(n.data()));
  taskDataSeq->inputs_count.emplace_back(n.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  auto testTaskOMP = std::make_shared<troitskiy_a_omp_integral_trapezoid::TestOMPTaskParalleltroitskiyIntegralTrapezoid>(
      taskDataSeq, sin_cos);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  perfAttr->current_timer = [&] { return omp_get_wtime(); };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskOMP);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_NEAR(res, out[0], 0.02);
}