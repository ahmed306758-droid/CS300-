-MODULE 8 Journal
-
-
- **Problem:** Build a command-line C++ program to read a course-data file, store courses in a data structure, and provide a menu to
-  (1) load the file, (2) print an alphanumeric list of CSCI and
-   MATH courses, (3) display a course’s title and prerequisites, and (9) exit; the original `Project 2 - ABCUVector.cpp`
-   was broken and needed a correct implementation that reads courselist  
*Approach & why data structures matter:** I parsed each CSV line into a `Course` struct and stored entries in `vector<Course>`. 
Vectors give simple indexed storage, easy iteration, 
and work with std::sort" for alphanumeric ordering; using a dedicated struct keeps data 
coherent and makes lookups (linear or later indexed) straightforward — choosing the right structure 
makes sorting, lookup, and extension easier and more efficient.  
  **Roadblocks & fixes:** The provided file had syntax and logic errors, and filename/compil
hassles due to spaces. I rewrote a clean CSV parser, added `trim`/`split` helpers, validated inputs,
copied the fixed file to a safe name (ABCUVector_fixed.cpp), compiled, and ran scripted tests against `fraction.csv` to verify behavior.  
  **How the project changed my software-design approach:** I emphasized single-responsibility functions
  (parsing, loading, sorting, printing), clear data modeling (`Course`), and user-facing validation/error messages. T
 hat structure makes it easier to reason about behavior, test components, and extend functionality (e.g., add indexing or different file formats).  
  *Maintainability, readability, adaptability improvements:** I used descriptive names, small helper functions, in-code comments, and avoided duplicating logic; I preserved immutability where
   helpful (copy-before-sort) and centralized lookup logic (`findCourseById`). These choices make the program easier to read, debug, and adapt (for example, swapping `vector` for a map for faster lookup or adding more course fields).
