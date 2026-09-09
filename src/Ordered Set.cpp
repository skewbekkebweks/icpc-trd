#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, std::less<int>, rb_tree_tag,tree_order_statistics_node_update>

ordered_set o_set;

o_set.insert(2);

// Finding the second smallest element
*(o_set.find_by_order(1))

// Finding the number of elements strictly less than k=4
o_set.order_of_key(4)

// Deleting 2 from the set if it exists
if (o_set.find(2) != o_set.end()) o_set.erase(o_set.find(2));
