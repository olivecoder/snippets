/* Search an array of sorted numbers.
*
* items    : An array of sorted ints, with no duplicates
* n_items  : Number of elements in the items array
* ascending: non-zero if the array is sorted in ascending order
* key      : the key to search for
* type     : the type of match to find
*
* This function finds the element in the array
* that best fits the search criteria. It returns
* the match type and the index of the matching item.
*
* LessThan
* --------
*  Finds the largest item which is less than the key.
*  It returns FoundLess if a match is found, NotFound
*  if no match is found.
*
* LessThanEquals
* --------------
*  Finds the item which is equal to the key, or the
*  largest item which is less than the key. Returns
*  FoundExact if an item that exactly matches the key
*  is found, FoundLess if a non-exact match is found
*  and NotFound if no match is found.
*
* Equals
* ------
*  Finds an item which is equal to the key. Returns
*  FoundExact if an item if found, NotFound otherwise.
*
* GreaterThanEquals
* -----------------
*  Finds the item which is equal to the key, or the
*  smallest item which is greater than the key. Returns
*  FoundExact if an item that exactly matches the key
*  is found, FoundGreater if a non-exact match is found
*  and NotFound if no match is found.
*
* GreaterThan
* -----------
*  Finds the smallest item which is greater than the
*  key. Returns FoundGreater if a match if found, NotFound
*  if no match is found.
*
* Examples
* --------
*  Given the input array [0, 2, 4, 6, 8] (ascending order)
*
*  +-----+-------------------+--------------+-------+
*  | Key | Type              | Returns      | Index |
*  +-----+-------------------+--------------+-------+
*  | -1  | LessThanEquals    | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  0  | LessThan          | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  0  | Equals            | FoundExact   | 0     |
*  +-----+-------------------+--------------+-------+
*  |  1  | Equals            | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThanEquals | FoundExact   | 1     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThan       | FoundGreater | 2     |
*  +-----+-------------------+--------------+-------+
*
*  Given the input array [8, 6, 4, 2, 0] (descending order)
*
*  +-----+-------------------+--------------+-------+
*  | Key | Type              | Returns      | Index |
*  +-----+-------------------+--------------+-------+
*  | -1  | LessThan          | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  4  | LessThanEquals    | FoundExact   | 2     |
*  +-----+-------------------+--------------+-------+
*  |  8  | Equals            | FoundExact   | 0     |
*  +-----+-------------------+--------------+-------+
*  |  5  | GreaterThanEquals | FoundGreater | 1     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThanEquals | FoundExact   | 3     |
*  +-----+-------------------+--------------+-------+
*  |  9  | GreaterThan       | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*
* Assumptions
* -----------
*  The items are sorted
*  Items will be non-NULL
*  There are no duplicate items
*  n_items will be > 0
*/

#include <assert.h>
#include <stdio.h> 

typedef enum {
    LessThan = 0,
    LessThanEquals = 1,
    Equals = 2,
    GreaterThanEquals = 3,
    GreaterThan = 4
} SearchType;
 
typedef enum {
    NotFound,
    FoundExact,
    FoundGreater,
    FoundLess
} SearchResult;
 

SearchResult Search(
    const int * const items,
    const int n_items,
    const int ascending,
    const int key,
    const SearchType type,
    int* const index )
{
    SearchResult search_result = NotFound; 
    int ix, step_direction;
    
    // search for item greater than or equals to key
    if ( ascending ) {
        for (ix = 0; ix < n_items && items[ix] < key; ix++);
        step_direction = 1;  
    } else { // if descending
        for (ix = n_items-1; ix >= 0 && items[ix] < key; ix--);
        step_direction = -1; 
    }

    if ( ix < 0 || ix >= n_items ) { 
        // the greater than or equals one was not found
        // the less one is the previous item
        if ( type == LessThan || type == LessThanEquals ) { 
                ix -= step_direction; 
                search_result = FoundLess;
        }
    } else if ( items[ix] == key ) { 
        // the current item is the exact match 
        // the greater one is the next 
        // the less one is on the previous item
        switch (type) { 
            case Equals:
            case LessThanEquals:
            case GreaterThanEquals:
                search_result = FoundExact;
                break;
            case LessThan:
                ix -= step_direction; // bounds checked later
                search_result = FoundLess;
                break;
            case GreaterThan:
                ix += step_direction; // bounds checked later
                search_result = FoundGreater;
                break;
        }
    } else {
        // the greater one is in the current index
        // the less one is the previous item
        switch (type) {
            case LessThan:
            case LessThanEquals: 
                ix -= step_direction; // bounds checked later
                search_result = FoundLess;
                break;
            case GreaterThan:
            case GreaterThanEquals:
                search_result = FoundGreater;
                break;
        }
    }

    // final array bounds checking
    if ( ix < 0 || ix >= n_items ) { 
        search_result = NotFound;
    } else { 
        // return a sane index
        *index = ix; 
    } 

    return search_result;
}

static
int test_do_Search(
    const int * const items,
    const int n_items,
    const int ascending,
    const int key,
    const SearchType type,
    const SearchResult expected_result) 
{
    int index;
    SearchResult search_result;
    int errors = 0;

    search_result = Search(items, n_items, ascending, key, type, &index);
    if ( search_result != expected_result ) { 
        errors++;
    } else if ( search_result != NotFound ) {
        switch (type) {
            case LessThan:
                if ( !(items[index] < key) ) errors++;
                break;
            case LessThanEquals:
                if ( !(items[index] <= key) ) errors++;
                break;
            case Equals:
                if ( !(items[index] == key) ) errors++; 
                break;
            case GreaterThan:
                if ( !(items[index] > key) ) errors++;
                break;
            case GreaterThanEquals:
                if ( !(items[index] >= key) ) errors++;
                break;
        }
    }

    if ( errors ) { 
        printf("SearchResult(): TEST CASE FAILURE: "
               "key=%i, ascending=%i, type=%i, expected result=%i, "
               "returned result=%i, index=%i, items[index]=%i\n", 
               key, ascending, type, expected_result,
               search_result, index, items[index]);
    }

    return errors;
}

static
int test_case_Search(int key, SearchType type, SearchResult result) 
{
    int ascending[] = { 1, 2, 3, 4, 6, 7, 8, 9 };
    int descending[] = { 9, 8, 7, 6, 4, 3, 2, 1 };
    int ascending_size = sizeof(ascending) / sizeof(*ascending);
    int descending_size = sizeof(descending) / sizeof(*descending);
    int errors = 0;

    errors += test_do_Search(ascending, ascending_size, 1, key, type, result);
    errors += test_do_Search(descending, descending_size, 0, key, type, result);
    return errors;
}

int test_Search(void) {
    int errors = 0;

    // Not found cases
    errors += test_case_Search( 0, Equals, NotFound );
    errors += test_case_Search( 0, LessThan, NotFound );
    errors += test_case_Search( 0, LessThanEquals, NotFound );
    errors += test_case_Search( 5, Equals, NotFound );
    errors += test_case_Search( 10, GreaterThan, NotFound );
    errors += test_case_Search( 10, GreaterThanEquals, NotFound );
    errors += test_case_Search( 1, LessThan, NotFound );
    errors += test_case_Search( 9, GreaterThan, NotFound );

    // FoundLess cases
    errors += test_case_Search( 10, LessThan, FoundLess );
    errors += test_case_Search( 10, LessThanEquals, FoundLess );
    errors += test_case_Search( 9, LessThan, FoundLess );
    errors += test_case_Search( 2, LessThan, FoundLess );
    errors += test_case_Search( 5, LessThan, FoundLess );
    errors += test_case_Search( 5, LessThanEquals, FoundLess );

    // FoundGreater
    errors += test_case_Search( 0, GreaterThan, FoundGreater );
    errors += test_case_Search( 0, GreaterThanEquals, FoundGreater );
    errors += test_case_Search( 5, GreaterThan, FoundGreater );
    errors += test_case_Search( 5, GreaterThanEquals, FoundGreater );

    // FoundExact
    errors += test_case_Search( 1, Equals, FoundExact );
    errors += test_case_Search( 1, LessThanEquals, FoundExact );
    errors += test_case_Search( 1, GreaterThanEquals, FoundExact );
    errors += test_case_Search( 9, Equals, FoundExact );
    errors += test_case_Search( 9, LessThanEquals, FoundExact );
    errors += test_case_Search( 9, GreaterThanEquals, FoundExact );
    errors += test_case_Search( 4, Equals, FoundExact );
    errors += test_case_Search( 4, LessThanEquals, FoundExact );
    errors += test_case_Search( 4, GreaterThanEquals, FoundExact );

	return errors
}

#ifdef RUN_TEST
int main() {
    int errors = test_Search();
	if ( errors ) { 
        printf("%i errors found\n", errors);
    } else { 
        printf("PASSED\n");
    }
}
#endif
