#include <gtest/gtest.h>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "core/task/include/task.hpp"
#include "seq/oturin_a_gift_wrapping/include/ops_seq.hpp"

TEST(oturin_a_gift_wrapping_seq, test_pipeline_run) {
  int kCount = 100000;
  using namespace oturin_a_gift_wrapping_seq;

  // Create data
  std::vector<coord> in(kCount, {0, 0});
  in.push_back({0, 1});
  in.push_back({1, -1});
  in.push_back({-1, -1});
  std::vector<coord> out(3);

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  auto test_task_sequential = std::make_shared<oturin_a_gift_wrapping_seq::TestTaskSequential>(task_data_seq);

  // Create Perf attributes
  auto perf_attr = std::make_shared<ppc::core::PerfAttr>();
  perf_attr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perf_attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perf_results = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perf_analyzer = std::make_shared<ppc::core::Perf>(test_task_sequential);
  perf_analyzer->PipelineRun(perf_attr, perf_results);
  ppc::core::Perf::PrintPerfStatistic(perf_results);
  ASSERT_EQ(out[0].x, -1);
  ASSERT_EQ(out[1].x, 0);
  ASSERT_EQ(out[2].x, 1);
}

TEST(oturin_a_gift_wrapping_seq, test_task_run) {
  int kCount = 100000;
  using namespace oturin_a_gift_wrapping_seq;

  // Create data
  std::vector<coord> in(kCount, {0, 0});
  in.push_back({0, 1});
  in.push_back({1, -1});
  in.push_back({-1, -1});
  std::vector<coord> out(3);

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  auto test_task_sequential = std::make_shared<oturin_a_gift_wrapping_seq::TestTaskSequential>(task_data_seq);

  // Create Perf attributes
  auto perf_attr = std::make_shared<ppc::core::PerfAttr>();
  perf_attr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perf_attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perf_results = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perf_analyzer = std::make_shared<ppc::core::Perf>(test_task_sequential);
  perf_analyzer->TaskRun(perf_attr, perf_results);
  ppc::core::Perf::PrintPerfStatistic(perf_results);

  ASSERT_EQ(out[0].x, -1);
  ASSERT_EQ(out[1].x, 0);
  ASSERT_EQ(out[2].x, 1);
}
