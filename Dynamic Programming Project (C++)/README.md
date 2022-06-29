# Crane unloading problem
Crane unloading problem

Daniel Cao
dcao182@csu.fullerton.edu

Determining Big-O for dynamic programming algorithm:

// grid must be non-empty.
assert(setting.rows() > 0);                                                             // 1 time unit
assert(setting.columns() > 0);                                                          // 1 time unit

using cell_type = std::optional<path>;                                                  // 1 time unit

std::vector<std::vector<cell_type>> A(setting.rows(),
                                      std::vector<cell_type>(setting.columns()));       // 1 time unit

A[0][0] = path(setting);                                                                // 1 time unit
assert(A[0][0].has_value());                                                            // 1 time unit

for (coordinate r = 0; r < setting.rows(); ++r) {                                       // for loop 1, n time units
  for (coordinate c = 0; c < setting.columns(); ++c) {                                  // for loop 2, n time units
    if (setting.get(r, c) != CELL_BUILDING) {                                           // if statement #1, 1 time unit

    cell_type from_above;                                                               // 1 time unit
    cell_type from_left;                                                                // 1 time unit

    if (r > 0 && A[r - 1][c].has_value()) {                                             // if statement #2, 2 time units
      from_above = A[r - 1][c];                                                         // 1 time unit

      if (from_above->is_step_valid(STEP_DIRECTION_SOUTH)) {                             // if statement #3, 1 time unit
        from_above->add_step(STEP_DIRECTION_SOUTH);                                       // 1 time unit
      }
    }

    if (c > 0 && A[r][c - 1].has_value()) {                                              // if statement #4, 2 time unit
      from_left = A[r][c - 1];                                                           // 1 time unit

      if (from_left->is_step_valid(STEP_DIRECTION_EAST)) {                               // if statement #5, 1 time unit
        from_left->add_step(STEP_DIRECTION_EAST);
      }
    }

    if (from_above.has_value() && from_left.has_value()) {                                 // if statement #6, 1 time unit
      if (from_above->total_cranes() > from_left->total_cranes()) {                        // if statement #7, 1 time unit
        A[r][c] = from_above;                                                             // 1 time unit
      }
      else {
        A[r][c] = from_left;                                                                // 1 time unit
      }
    }
    else if (from_above.has_value() && !from_left.has_value()) {                            // if statement #8, 1 time unit
      A[r][c] = from_above;                                                                 // 1 time unit
    }
    else if (from_left.has_value() && !from_above.has_value()) {                              // if statement #9, 1 time unit
      A[r][c] = from_left;                                                                    // 1 time unit
    }
    else {                                                                                    // if statement #10, 3 time units
      A[r][c] = path(setting);                                                                // 1 time unit
    }
  }
}

cell_type* best = &(A[0][0]);                                                                 // 1 time unit
assert(best->has_value());                                                                      // 1 time unit
for (coordinate r = 0; r < setting.rows(); ++r) {                                             // n time units
  for (coordinate c = 0; c < setting.columns(); ++c) {                                          // n time units
    if (A[r][c].has_value() && (A[r][c]->total_cranes() > (*best)->total_cranes())) {           // if statement #11, 2 time units
      best = &(A[r][c]);                                                                         // 1 time unit
    }
  }
}

assert(best->has_value());                                                                        // 1 time unit
//   std::cout << "total cranes" << (**best).total_cranes() << std::endl;

return **best;                                                                                      // 1 time unit




step count for if statement #3: 2

step count for if statement #2: 2 + 2 + 1 = 5

step count for if statement #5: 2

step count for if statement #4: 2 + 2 + 1 = 5

step count for if statement #10: 3 + 1 = 4

step count for if statement #9: 1 + max(1, 4) = 5

step count for if statement #8: 1 + max(1 + 2) = 3

step count for if statement #7: 1 + max(1 + 1) = 2

step count for if statement #6: 1 + max(2, 2) = 3

step count for if statement #1: 1 + 2 + 5 + 2 + 5 + 4 + 5 + 3 + 2 + 3 = 32

step count nested for loops: n^2 * 32 = 32(n^2) + 2

step count for second set of nested for loops: n * n + 2 = 2(n^2) + 2

step count for the dynamic programming algorithm: 32(n^2) + 2(n^2) + 4 = 34(n^2) + 4

big-O efficiency: 34(n^2) + 4

we prove 33(n^2) + 4 belongs to O(n^2) with the limit theorem.

lim            34(n^2) + 4 = O(n^2)
n -> infinite

we divide both sides by n^2

= lim           34 + (4 / n^2)
  n -> infinite

= 34 + (4 / infinite)
= 34 + 0
= 34

Since the limit is a constant that is greater than or equal to 0, proven by the limit theorem, 34(n^2) + 4 belongs to O(n^2).

The big-O efficiency is O(n^2).









Determining step count for exhaustive optimization algorithm:


  // grid must be non-empty.
  assert(setting.rows() > 0);                                                   // 1 time unit
  assert(setting.columns() > 0);                                                // 1 time unit

  // Compute maximum path length, and check that it is legal.
  const size_t max_steps = setting.rows() + setting.columns() - 2;              // 3 time units
  assert(max_steps < 64);                                                       // 1 time unit

  path best(setting);                                                           // 1 time unit

  for (size_t steps = 1; steps <= max_steps; ++steps) {                         // for loop #1, n - 1 + 1 time units
    uint64_t mask = uint64_t(1) << steps;                                       // 2 time units
    for (uint64_t bits = 0; bits < mask; ++bits) {                              // for loop #2, 2^n time units

      path candidate(setting);                                                  // 1 time unit
      bool valid = true;                                                        // 1 time unit
        // add to candidate a path not exceedings <steps> binary values
      for (size_t k = 0; k < steps; k++) {                                      // for loop #3, n - 1 - 0 + 1 time units
          int bit = (bits >> k) & 1;                                            // 3 time units

          if (bit == 1) {                                                       // if statement #1, 1 time unit
            if (candidate.is_step_valid(STEP_DIRECTION_EAST)) {                 // if statement #2, 1 time unit
              candidate.add_step(STEP_DIRECTION_EAST);                          // 1 time unit
            }
            else {
              valid = false;                                                    // 1 time unit
              break;                                                            // 1 time unit
            }
          }
          else {
            if (candidate.is_step_valid(STEP_DIRECTION_SOUTH)) {                // if statement #3, 1 time unit
              candidate.add_step(STEP_DIRECTION_SOUTH);                         // 1 time unit
            }
            else {
              valid = false;                                                    // 1 time unit
              break;                                                            // 1 time unit
            }
          }
      }

      if (valid && (candidate.total_cranes() > best.total_cranes())) {          // if statement #4, 2 time unit
        best = candidate;                                                       // 1 time unit
      }
    }
  }
  return best;                                                                  // 1 time unit



step count for for block of for loop 3:

step count for if statement #2: 1 + max(1 + 2) = 3
step count for if statement #3: 1 + max(1 + 2) = 3
step count for if statement #1: 1 + max(3, 3) = 4
step count for for for block of for loop #3: n * (3 + 4) = 7n

step count for if statement #4: 2 + 1 = 3

step count for for block for for loop #2: 2 + 7n + 3 = 7n + 5

step count for for loop #2: 2^n * (7n + 5)

step count for  for loop #1: n * (2^n * (7n + 5))

step count for the exhaustive optimization algorithm: n * (2^n * (7n + 5))




To prove with the limit theorem that n * (2^n * (7n + 5)) belongs to O(2^n * n),

we divide both sides by 2^n * n

lim           n * (2^n * (7n + 5)) / (2^n * n)
n -> infinite

lim           ( n / (2^n * n) ) * (2^n * (7n + 5)) / (2^n * n)
n -> infinite

lim          (1 / 2^n) * (7n + 5) / n
n -> infinite

lim          (1 / 2^n) * (7n / n + 5 / n)
n -> infinite

lim         (1 / 2^n) * (7 + (5 / n))
n -> infinite

= 0 * (7 + 0)

= 0

Therefore, proven by the limit theorem, since the limit is a constant, 0, which is greater than or equal to zero, the f(n), n * (2^n * (7n + 5)), belongs to O(2^n * n).

The big-O efficiency is O(2^n * n).
