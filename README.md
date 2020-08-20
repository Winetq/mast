# mast  
The program reads a set of n rooted trees in the NEWICK format, and then for each of n(n-1)/2 pairs of trees will calculate the minimum number of leaves whose removal from both
trees will make them isomorphic. The problem is known in IT as maximum agreement subtree problem. Considered trees have 10 leaves labeled from 1 to 10. Example input and output:  

4  
(1,5,(10,6,3),(2,(8,7)),(9,4));  
((7,(3,(4,9,(1,2)))),8,(5,(10,6)));  
(7,((6,(9,5),(8,3)),(1,(2,10,4))));  
(7,(8,3,4,6,1),(9,5,10),2);  

5 (in my solution it is 6 beacuse in the function mast() I use greedy algorithm instead of for example brute force)  
7  
6  
6  
6  
6  
