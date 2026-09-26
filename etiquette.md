
# Vector, Array, List, Map
- **`<T> []`** - a fixed size array that assigns memory at the start 
  - Immutable but quick to fsearch/index
- **`std::vector<T>`** — a growable array that owns and manages its own memory. 
  - Mutable but adding a new element -> create a new variable, allocate a larger memory to the new variable, and copy the content of the old vector to the new vector
- **`std::list<T>`** - doubly link list that is growable
  - Randomly select points is not possible -> need to iterate the list from either the start or the end
- **`std::map<T>`** - lookup table with a key and a value
  - Get the best of a list and an array
- **`std::string`** — a growable, owning text string; no manual buffers, no `strcpy`.

# Useful functions/algorithms
## **`#include <algorithm>`**  
  - **`#std::sort`** - sort the data structure
    -   std::sort(data.begin(), data.end());
  - **`#std::find_if`** - use a lambda expression to the first item in a data structure
    - auto it = std::find_if(data.begin(), data.end(),[](int v) { return v >= 7; });
##  **`#include <numeric>`**     
  - **`#std::accumulate`** - sum up all the values
    - int sum  = std::accumulate(data.begin(), data.end(), 0);
