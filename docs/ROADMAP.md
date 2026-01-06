# ElectricDB Development Roadmap

This document defines a **clear, ordered roadmap** for building ElectricDB based on the *actual repository structure*. The goal is to maximize correctness, performance, and architectural stability while minimizing rewrites.

The ordering here is deliberate and reflects how modern analytical engines (DuckDB, HyPer, MonetDB) are built.

---

## Phase 0 — Build & Project Foundations

**Objective:** Make the project boring to build and easy to reason about.

### Scope

* CMake target-per-directory structure
* `project_options` interface target
* Namespaced headers under `src/include/electricdb`
* Sanitizers in Debug builds
* GoogleTest integration

### Exit Criteria

* Clean `cmake -S . -B build`
* No cyclic CMake dependencies
* All tests runnable via `ctest`

---

## Phase 1 — Core Utilities (`src/util`)

**Why first:** Every layer above depends on fast, predictable memory and utilities.

### 1. Arena Allocator

**Directory:** `src/util`

Responsibilities:

* Bump-pointer allocation
* Alignment guarantees
* Fast reset semantics

Tasks:

* Arena growth strategy
* `bytes_used()` / `bytes_reserved()`
* Deterministic behavior
* Unit tests (`tests/util/arena_test.cpp`)

Exit Criteria:

* Arena passes stress tests
* No per-allocation `malloc`

---

### 2. Supporting Utilities

Tasks:

* Hash utilities
* Set up SIMD helpers
* Set up Stopwatch / timing helpers

Exit Criteria:

* Used by execution layer without changes

---

## Phase 2 — Vectorized Execution Primitives (`src/execution/vector`)

**This is the heart of the system. Do not rush this phase.**

### 3. SelectionVector

Responsibilities:

* Row indirection
* Filtering without data movement

Tasks:

* Index storage
* Reset / resize
* Stable iteration
* Unit tests

---

### 4. NullMask

Responsibilities:

* Compact NULL tracking

Tasks:

* Bit-packed representation
* Set / clear / reset
* Bounds safety
* Unit tests

---

### 5. Vector

Responsibilities:

* Owns or references columnar data
* Couples data + nullmask + selection

Tasks:

* Type-erased storage
* Fixed-width primitive support
* Nullable semantics
* Referencing vs owning vectors
* Slicing semantics
* Unit tests

Exit Criteria:

* Vectors usable without storage layer

---

## Phase 3 — Expressions (`src/execution/expressions`)

### 6. Expression Evaluation

Responsibilities:

* Vectorized scalar computation

Tasks:

* Expression tree
* Unary / binary operators
* Constant folding
* Vector-at-a-time evaluation

---

### 7. (Optional) Expression Codegen

Future work:

* LLVM or bytecode backend
* Interpreter/JIT boundary

---

## Phase 4 — Execution Engine (`src/execution`)

### 8. Engine Core

Directories:

* `engine`
* `memory`

Responsibilities:

* Operator interface
* Pipeline construction
* Scheduling
* Query-local memory

Tasks:

* Pull-based operator API
* Pipeline builder
* Scheduler
* QueryArena + spill manager

---

### 9. Physical Operators (`src/execution/operators`)

**Implementation order matters:**

1. Scan
2. Filter
3. Projection
4. Aggregate
5. Join
6. Sort
7. Out

Each operator:

* Vectorized
* Stateless where possible
* Independently testable

Exit Criteria:

* Operators compose into pipelines

---

## Phase 5 — Storage Layer (`src/storage`)

**Storage comes *after* execution semantics are stable.**

### 10. Column Storage

Responsibilities:

* Immutable column chunks
* Compression-friendly layout

Tasks:

* Column chunks
* Zone maps
* Column readers/writers

---

### 11. Encodings

Tasks:

* Plain
* RLE
* Dictionary
* Delta / FOR

Exit Criteria:

* Scan operator backed by real storage

---

## Phase 6 — Catalog & Metadata (`src/catalog`)

Responsibilities:

* Schemas
* Snapshots
* Statistics

Tasks:

* Statistics propagation
* Snapshot correctness

---

## Phase 7 — Planner (`src/planner`)

### 12. Logical Planning

Tasks:

* Logical nodes
* Rule-based rewrites

---

### 13. Physical Planning

Tasks:

* Cost model
* Join ordering
* Operator selection

Exit Criteria:

* Logical → Physical plan lowering

---

## Phase 8 — SQL Frontend (`src/sql`)

Responsibilities:

* User-facing SQL layer

Tasks:

* Parser
* Binder
* Semantic analysis
* SQL → logical plan

---

## Phase 9 — Runtime (`src/runtime`)

Responsibilities:

* Query lifecycle
* Cancellation
* Metrics

Tasks:

* Resource tracking
* Result materialization

---

## Phase 10 — Integration & Hardening

### 18. End-to-End Execution

Tasks:

* SQL → execution pipeline
* Result correctness tests

---

### 19. Performance & Stability

Tasks:

* Benchmarks
* Memory profiling
* Threading
* NUMA awareness

---

## Phase 11 — Production Readiness

Tasks:

* CI benchmarks
* Fault injection
* Long-running stability tests

---

## Non-Negotiable Design Principles

* Vectors first
* Explicit memory ownership
* No hidden allocations
* No global state
* Every layer testable in isolation

---

## Final Note

Following this roadmap strictly:

* Avoids rewrites
* Surfaces performance issues early
* Keeps the system understandable

This ordering is intentional and proven.
