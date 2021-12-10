# 335-project-2
Daniel Cao
dcao182@csu.fullerton.edu


Calculating big-O efficiency for the greedy algorithm:

CargoVector todo = goods;                                             // 1 time unit
std::unique_ptr<CargoVector> result(new CargoVector);                 // 1 time unit
double result_volume = 0;                                             // 1 time unit
int i = 0;                                                            // 1 time unit
int indexOfBestItem = 0;                                              // 1 time unit

while (!todo.empty()) {                                               // n time units
  i = 0;                                                              // 1 time unit

  std::shared_ptr<CargoItem> cargoItem (new CargoItem(" ", 1, 0));    // 1 time unit

  for (auto & item : todo) {                                          // n time units
    double item_wpv = item->weight() / item->volume();                // 2 time units
    double cargoItem_wpv = cargoItem->weight() / cargoItem->volume(); // 2 time units

    if (item_wpv > cargoItem_wpv) {                                   // 1 time unit
      cargoItem = item;                                               // 1 time unit
      indexOfBestItem = i;                                            // 1 time unit
    }

    i++;                                                              // 1 time unit
  }

  todo.erase(todo.begin() + indexOfBestItem);                         // 1 time unit

  if ((result_volume + cargoItem->volume()) <= total_volume) {        // 2 time units
    result->push_back(cargoItem);                                     // 1 time unit
    result_volume += cargoItem->volume();                             // 1 time unit
  }
}
return result;                                                        // 1 time unit



  step count calculation:

  sc greedy algorithm: 5 + sc while loop + 1

  sc while loop: n * sc while block


  sc while block: 1 + 1 + sc for loop + 1 + if statement


  sc for loop: n * ( 2 + 2 + if statement ) + 1


  sc if statement in for loop: 1 + max(2, 0)
                  = 1 + 2
                  = 3

  sc for loop: n * ( 2 + 2 + 3 ) + 1
              = 8n + 1

  sc while block: 1 + 1 + (8n + 1) + 1 + if statement

  sc if statement #2: 2 + max(2, 0)
                      = 2 + 2
                      = 4

  sc while block: 1 + 1 + (8n + 1) + 1 + (4)
                = 8n + 8

  sc while loop: n * (8n + 8)
                = 8n^2 + 8

  sc greedy algorithm: 5 + (8n^2 + 8) + 1
                    = 8n^2 + 14

  calculated step count for greedy algorithm: 8n^2 + 14


For the step count of the step count, we want to show that 8n^2 + 14 belongs to O(n^2).  
By the limit theorem, we solve ( f(n) ) / ( g(n) ) as n approaches infinite, if the limit is greater than or equal to 0 and is a constant, f(n) belongs to O(g(n)).  
If the limit is infinite then the f(n) does not belong to O(g(n)).  
Using the limit theorem, we solve ( 8n^2 + 14 ) / (n^22 ) as n approaches infinite.  
We separate f(n) into two fractions.  
lim           ( 8n^2 / n^2 ) + lim          ( 14 / n^2 )
n -> infinite	                n -> infinite		  

= 8 + 0
= 8

Therefore, proven by the limit theorem, since the limit is a constant, 8, which is greater than or equal to zero, the f(n), 8n^2 + 14, belongs to O(n^2).




Calculation for step count for the filter_cargo_vector

std::unique_ptr<CargoVector> filter_cargo_vector
(
	const CargoVector& source,
	double min_weight,
	double max_weight,
	int total_size
)
{
	std::unique_ptr<CargoVector> result(new CargoVector);          // 1 time unit

	for (auto & item : source) {                                   // n time units
		if (item->weight() >= min_weight
												&& item->weight() <= max_weight
												&& result->size() != total_size) {       // 5 time units
			result->push_back(item);                                   // 1 time unit
		}
	}

	return result;                                                 // 1 time unit
}



step count calculation:

step count for if statement:
5 + max(1, 0)
= 5 + 1
= 6



step count for for loop:
n * 6
= 6n



step count for filter_cargo_vector:
1 + 6n + 1
= 6n + 2



calculated step count for filter_cargo_vector:
6n + 2



For the step count of the step count, we want to show that 6n + 2 belongs to O(n).  
By the limit theorem, we solve ( f(n) ) / ( g(n) ) as n approaches infinite, if the limit is greater than or equal to 0 and is a constant, f(n) belongs to O(g(n)).  
If the limit is infinite then the f(n) does not belong to O(g(n)).  
Using the limit theorem, we solve ( 6n + 2 ) / n as n approaches infinite.  
We separate f(n) into two fractions.  
lim           ( 6n / n ) + lim           ( 2 / n )
n -> infinite	             n -> infinite		  

= 6 + 0
= 6

Therefore, proven by the limit theorem, since the limit is a constant, 6, which is greater than or equal to zero, the f(n), 6n + 2, belongs to O(n).







Calculation for big-O efficiency for the exhaustive optimization algorithm:

  const int n = goods.size();                                    // 1 time unit
	assert(n < 64);                                                // 1 time unit
	std::unique_ptr<CargoVector> best(new CargoVector);            // 1 time unit
	double total_cand_weight = 0;                                  // 1 time unit
	double total_cand_volume = 0;                                  // 1 time unit
	double total_best_weight = 0;                                  // 1 time unit
	double total_best_volume = 0;                                  // 1 time unit

	for (int bits = 0; bits < pow(2, n); bits++) {                 // 2^n time units
		std::unique_ptr<CargoVector> candidate(new CargoVector);     // 1 time unit

		for (int j = 0; j < n; j++) {                                // n time units
			if ((bits >> j) & 1 == 1) {                                // 3 time units
				candidate->push_back(goods[j]);                          // 1 time unit
			}
		}

		sum_cargo_vector(*candidate, total_cand_volume, total_cand_weight);     // 1 time unit

		if (total_cand_volume <= total_volume) {                                // 1 time unit
			if (best->empty() || total_cand_weight > total_best_weight) {         // 2 time units
				*best = *candidate;                                                 // 1 time unit
				total_best_weight = total_cand_weight;                              // 1 time unit
			}
		}
	}

	return best;                                                              // 1 time units



  step count calculation:

  sc exhaustive optimization algorithm: 7 + for loop + 1

  sc for loop: 2^n * for block


  sc for block: 1 + for loop + 1 + if statement

  sc for loop #2: n * if statement

  sc if statement: 3 + max(1, 0)
                  = 3 + 1
                  = 4

  sc for loop #2: n * (4)
                  = 4n

  sc for block: 1 + (4n) + 1 + if statement

  sc if statement: 1 + max(if statement, 0)

  sc if statement: 2 + max(2, 0)
                    = 2 + 2
                    = 4

  sc if statement: 1 + max(4, 0)
                  = 1 + 4
                  = 5

  sc for block: 1 + (4n) + 1 + (5)
              = 4n + 7

  sc for loop: 2^n * (4n + 7)
              = 2^n * 4n + 7

  sc exhaustive optimization algorithm: 7 + (2^n * 4n + 7) + 1
                                      = 2^n * 4n + 15

  calculated step count for exhaustive optimization algorithm: 2^n * 4n + 15



  For the step count of the step count, we want to show that 2^n * 4n + 15 belongs to O(2^n * n).  
  By the limit theorem, we solve ( f(n) ) / ( g(n) ) as n approaches infinite, if the limit is greater than or equal to 0 and is a constant, f(n) belongs to O(g(n)).  
  If the limit is infinite then the f(n) does not belong to O(g(n)).  
  Using the limit theorem, we solve ( 2^n * 4n + 15 ) / ( 2^n * n ) as n approaches infinite.  
  We separate f(n) into three fractions.  
  lim           ( 2^n / 2^n * n ) + lim          ( 4n / 2^n * n ) + lim           ( 15 / 2^n * n )
  n -> infinite	                    n -> infinite		                n -> infinite

  = 0 + 0 + 0
  = 0

  Therefore, proven by the limit theorem, since the limit is a constant, 0, which is greater than or equal to zero, the f(n), 2^n * 4n + 15, belongs to O(2^n * n).
