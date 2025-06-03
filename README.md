This is a joke algorithm I came up with during sixth form. "BogoSearch" is a searching algorithm based on the "incredible" BogoSort algorithm.<br/>
<br/>
The algorithm works like this:<br/>
~A set of data is taken as an input, an element is chosen as the "desired element", either by the user or randomly<br/>
~Randomly generate a number<br/>
~Does this number match up with the index of our desired element?<br/>
-Yes: search complete, return the selected element<br/>
-No: go again from step 2<br/>
<br/>
This specific program features:<br/>
~A GUI where the user can select the selection speed (fps) and the amount of indices the algorithm will need to search through.<br/>
~a visualiser that shows what the algorithm is doing (the amount of indices, the desired element and the index the algorithm has currently selected)<br/>
~A recording of the time taken for the algorithm to find.<br/>
<br/>
For now, this project is, for the most part, considered complete, however, I do have an idea for some extra features, such as saving the best time for a given configuration (amount of indices and fps). There are also some other QOL/code refactors that could also be implemented in the future, but this was always intended to be a silly joke project, so im not too worried about that right now.<br/>

This project is using a **very** early version of my "Arrow Engine" library (from before I even made it into a proper library) for buttons, incrementors and most other GUI things. Expect to see documentation for stuff like that on that project's page (although the readability of my code and it's comments should already give you the info you need ;p ). 
