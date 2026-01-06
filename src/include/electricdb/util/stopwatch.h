#pragma once

#include <cstdint>

namespace electricdb {

class Stopwatch {
  public:
	Stopwatch();

	void start();
	void stop();
	void reset();

	// Elapsed time
	uint64_t elapsed_ns() const;
	double elapsed_ms() const;
	double elapsed_sec() const;

	bool running() const;

  private:
	uint64_t start_ns_ = 0;
	uint64_t accumulated_ns_ = 0;
	bool running_ = false;
};

} // namespace electricdb
