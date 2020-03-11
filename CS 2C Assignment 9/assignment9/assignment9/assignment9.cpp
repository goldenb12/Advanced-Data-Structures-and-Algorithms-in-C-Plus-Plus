/*
Name: Brandon Goldenberg
Class: Foothill College CS 2C
Date: 3/17/2020
Instructor: Eric Reed
File Name: assignment9.cpp

Program Description: This program implements a maximum flow graph algorithm
using a template class, FHflowGraph.  The input graph is communicated to the
FHflowGraph object by the client using any reasonable technique that takes
underlying object data (string, doubles, etc.); the method addEdge() is used
in the FHflowGraph template.  Start and end vertices are set using the mutators
setStartVert() and setEndVert().  A findMaxFlow() public method is used to
invoke the algorithm and return the maximum flow supported by the input graph.
After the method is called, the client should be able to call I/O methods
showFlowAdjTable() and showResAdjTable() to show both the flow graph and the
residual graph that result from the recent call to findMaxFlow().  
*/

#include <iostream>
#include <string>
using namespace std;
#include "FHflowGraph.h"

// --------------- main ---------------
int main()
{
   int finalFlow;

   // build graph
   FHflowGraph<string, int> myG;

   // first test
   myG.addEdge("s", "a", 3);     myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1);     myG.addEdge("a", "c", 3);
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 2);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // second test
   myG.clear();
   myG.addEdge("s", "a", 3);     myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1);     myG.addEdge("a", "c", 3);
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 2);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // third test
   myG.clear();
   myG.addEdge("s", "a", 4);     myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1);     myG.addEdge("a", "c", 2);
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 3);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // fourth test
   myG.clear();
   myG.addEdge("s", "A", 1);     myG.addEdge("s", "D", 4);
   myG.addEdge("s", "G", 6);
   myG.addEdge("A", "B", 2);     myG.addEdge("A", "E", 2);
   myG.addEdge("B", "C", 2);
   myG.addEdge("C", "t", 4);
   myG.addEdge("D", "E", 3);     myG.addEdge("D", "A", 3);
   myG.addEdge("E", "C", 2);     myG.addEdge("E", "F", 3);
   myG.addEdge("E", "I", 3);
   myG.addEdge("F", "C", 1);     myG.addEdge("F", "t", 3);
   myG.addEdge("G", "D", 2);     myG.addEdge("G", "E", 1);
   myG.addEdge("G", "H", 6);
   myG.addEdge("H", "E", 2);     myG.addEdge("H", "I", 6);
   myG.addEdge("I", "F", 1);     myG.addEdge("I", "t", 4);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // fifth test
   myG.clear();

   myG.addEdge("s", "h", 5);
   myG.addEdge("h", "i", 5);
   myG.addEdge("i", "b", 5);
   myG.addEdge("a", "b", 5);
   myG.addEdge("s", "a", 5);
   myG.addEdge("s", "c", 5);
   myG.addEdge("s", "d", 5);
   myG.addEdge("a", "e", 5);
   myG.addEdge("e", "j", 5);
   myG.addEdge("j", "t", 5);
   myG.addEdge("d", "g", 5);
   myG.addEdge("g", "t", 5);
   myG.addEdge("b", "t", 5);
   myG.addEdge("c", "t", 5);
   myG.addEdge("d", "c", 5);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();


   // first test, redux
   myG.clear();
   myG.addEdge("s", "a", 3);     myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1);     myG.addEdge("a", "c", 3);
   myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 2);
   myG.addEdge("d", "t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // final exam graph analysis
   myG.clear();
   myG.addEdge("s", "a", 1);     myG.addEdge("s", "b", 2);
   myG.addEdge("s", "t", 4);
   myG.addEdge("a", "c", 1);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 1);
   myG.addEdge("d", "t", 2);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   return 0;
}

/*
 Output:

 ------------------------
 Residual Adj List for s: a(3) b(2)
 Residual Adj List for a: s(0) b(1) c(3) d(4)
 Residual Adj List for b: s(0) a(0) d(2)
 Residual Adj List for c: a(0) t(2)
 Residual Adj List for d: a(0) b(0) t(3)
 Residual Adj List for t: c(0) d(0)

 ------------------------
 Flow Adj List for s: a(0) b(0)
 Flow Adj List for a: b(0) c(0) d(0)
 Flow Adj List for b: d(0)
 Flow Adj List for c: t(0)
 Flow Adj List for d: t(0)
 Flow Adj List for t:

 Final flow: 5
 ------------------------
 Residual Adj List for s: a(0) b(0)
 Residual Adj List for a: s(3) b(1) c(1) d(3)
 Residual Adj List for b: s(2) a(0) d(0)
 Residual Adj List for c: a(2) t(0)
 Residual Adj List for d: a(1) b(2) t(0)
 Residual Adj List for t: c(2) d(3)

 ------------------------
 Flow Adj List for s: a(3) b(2)
 Flow Adj List for a: b(0) c(2) d(1)
 Flow Adj List for b: d(2)
 Flow Adj List for c: t(2)
 Flow Adj List for d: t(3)
 Flow Adj List for t:

 ------------------------
 Residual Adj List for s: a(3) b(2)
 Residual Adj List for a: s(0) b(1) c(3) d(4)
 Residual Adj List for b: s(0) a(0) d(2)
 Residual Adj List for c: a(0) t(2)
 Residual Adj List for d: a(0) b(0) t(3)
 Residual Adj List for t: c(0) d(0)

 ------------------------
 Flow Adj List for s: a(0) b(0)
 Flow Adj List for a: b(0) c(0) d(0)
 Flow Adj List for b: d(0)
 Flow Adj List for c: t(0)
 Flow Adj List for d: t(0)
 Flow Adj List for t:

 Final flow: 5
 ------------------------
 Residual Adj List for s: a(0) b(0)
 Residual Adj List for a: s(3) b(1) c(1) d(3)
 Residual Adj List for b: s(2) a(0) d(0)
 Residual Adj List for c: a(2) t(0)
 Residual Adj List for d: a(1) b(2) t(0)
 Residual Adj List for t: c(2) d(3)

 ------------------------
 Flow Adj List for s: a(3) b(2)
 Flow Adj List for a: b(0) c(2) d(1)
 Flow Adj List for b: d(2)
 Flow Adj List for c: t(2)
 Flow Adj List for d: t(3)
 Flow Adj List for t:

 ------------------------
 Residual Adj List for s: a(4) b(2)
 Residual Adj List for a: s(0) b(1) c(2) d(4)
 Residual Adj List for b: s(0) a(0) d(2)
 Residual Adj List for c: a(0) t(3)
 Residual Adj List for d: a(0) b(0) t(3)
 Residual Adj List for t: c(0) d(0)

 ------------------------
 Flow Adj List for s: a(0) b(0)
 Flow Adj List for a: b(0) c(0) d(0)
 Flow Adj List for b: d(0)
 Flow Adj List for c: t(0)
 Flow Adj List for d: t(0)
 Flow Adj List for t:

 Final flow: 5
 ------------------------
 Residual Adj List for s: a(1) b(0)
 Residual Adj List for a: s(3) b(1) c(0) d(3)
 Residual Adj List for b: s(2) a(0) d(0)
 Residual Adj List for c: a(2) t(1)
 Residual Adj List for d: a(1) b(2) t(0)
 Residual Adj List for t: c(2) d(3)

 ------------------------
 Flow Adj List for s: a(3) b(2)
 Flow Adj List for a: b(0) c(2) d(1)
 Flow Adj List for b: d(2)
 Flow Adj List for c: t(2)
 Flow Adj List for d: t(3)
 Flow Adj List for t:

 ------------------------
 Residual Adj List for B: C(2) A(0)
 Residual Adj List for E: C(2) F(3) D(0) A(0) G(0) I(3) H(0)
 Residual Adj List for C: B(0) E(0) t(4) F(0)
 Residual Adj List for t: C(0) F(0) I(0)
 Residual Adj List for F: E(0) C(1) t(3) I(0)
 Residual Adj List for D: E(3) s(0) A(3) G(0)
 Residual Adj List for s: D(4) A(1) G(6)
 Residual Adj List for A: B(2) E(2) D(0) s(0)
 Residual Adj List for G: E(1) D(2) s(0) H(6)
 Residual Adj List for I: E(0) t(4) F(1) H(0)
 Residual Adj List for H: E(2) G(0) I(6)

 ------------------------
 Flow Adj List for B: C(0)
 Flow Adj List for E: C(0) F(0) I(0)
 Flow Adj List for C: t(0)
 Flow Adj List for t:
 Flow Adj List for F: C(0) t(0)
 Flow Adj List for D: E(0) A(0)
 Flow Adj List for s: D(0) A(0) G(0)
 Flow Adj List for A: B(0) E(0)
 Flow Adj List for G: E(0) D(0) H(0)
 Flow Adj List for I: t(0) F(0)
 Flow Adj List for H: E(0) I(0)

 Final flow: 11
 ------------------------
 Residual Adj List for B: C(0) A(2)
 Residual Adj List for E: C(0) F(0) D(3) A(2) G(1) I(0) H(2)
 Residual Adj List for C: B(2) E(2) t(0) F(0)
 Residual Adj List for t: C(4) F(3) I(4)
 Residual Adj List for F: E(3) C(1) t(0) I(0)
 Residual Adj List for D: E(0) s(4) A(0) G(2)
 Residual Adj List for s: D(0) A(0) G(0)
 Residual Adj List for A: B(0) E(0) D(3) s(1)
 Residual Adj List for G: E(0) D(0) s(6) H(3)
 Residual Adj List for I: E(3) t(0) F(1) H(1)
 Residual Adj List for H: E(0) G(3) I(5)

 ------------------------
 Flow Adj List for B: C(2)
 Flow Adj List for E: C(2) F(3) I(3)
 Flow Adj List for C: t(4)
 Flow Adj List for t:
 Flow Adj List for F: C(0) t(3)
 Flow Adj List for D: E(3) A(3)
 Flow Adj List for s: D(4) A(1) G(6)
 Flow Adj List for A: B(2) E(2)
 Flow Adj List for G: E(1) D(2) H(3)
 Flow Adj List for I: t(4) F(0)
 Flow Adj List for H: E(2) I(1)

 ------------------------
 Residual Adj List for e: j(5) a(0)
 Residual Adj List for j: e(0) t(5)
 Residual Adj List for t: j(0) g(0) c(0) b(0)
 Residual Adj List for g: t(5) d(0)
 Residual Adj List for s: h(5) c(5) d(5) a(5)
 Residual Adj List for h: s(0) i(5)
 Residual Adj List for c: t(5) s(0) d(0)
 Residual Adj List for d: g(5) s(0) c(5)
 Residual Adj List for i: h(0) b(5)
 Residual Adj List for b: t(5) i(0) a(0)
 Residual Adj List for a: e(5) s(0) b(5)

 ------------------------
 Flow Adj List for e: j(0)
 Flow Adj List for j: t(0)
 Flow Adj List for t:
 Flow Adj List for g: t(0)
 Flow Adj List for s: h(0) c(0) d(0) a(0)
 Flow Adj List for h: i(0)
 Flow Adj List for c: t(0)
 Flow Adj List for d: g(0) c(0)
 Flow Adj List for i: b(0)
 Flow Adj List for b: t(0)
 Flow Adj List for a: e(0) b(0)

 Final flow: 20
 ------------------------
 Residual Adj List for e: j(0) a(5)
 Residual Adj List for j: e(5) t(0)
 Residual Adj List for t: j(5) g(5) c(5) b(5)
 Residual Adj List for g: t(0) d(5)
 Residual Adj List for s: h(0) c(0) d(0) a(0)
 Residual Adj List for h: s(5) i(0)
 Residual Adj List for c: t(0) s(5) d(0)
 Residual Adj List for d: g(0) s(5) c(5)
 Residual Adj List for i: h(5) b(0)
 Residual Adj List for b: t(0) i(5) a(0)
 Residual Adj List for a: e(0) s(5) b(5)

 ------------------------
 Flow Adj List for e: j(5)
 Flow Adj List for j: t(5)
 Flow Adj List for t:
 Flow Adj List for g: t(5)
 Flow Adj List for s: h(5) c(5) d(5) a(5)
 Flow Adj List for h: i(5)
 Flow Adj List for c: t(5)
 Flow Adj List for d: g(5) c(0)
 Flow Adj List for i: b(5)
 Flow Adj List for b: t(5) a(-5)
 Flow Adj List for a: e(5) b(5)

 ------------------------
 Residual Adj List for s: a(3) b(2)
 Residual Adj List for a: s(0) b(1) d(4) c(3)
 Residual Adj List for b: s(0) a(0) d(2)
 Residual Adj List for d: a(0) b(0) t(3)
 Residual Adj List for c: a(0) t(2)
 Residual Adj List for t: d(0) c(0)

 ------------------------
 Flow Adj List for s: a(0) b(0)
 Flow Adj List for a: b(0) d(0) c(0)
 Flow Adj List for b: d(0)
 Flow Adj List for d: t(0)
 Flow Adj List for c: t(0)
 Flow Adj List for t:

 Final flow: 5
 ------------------------
 Residual Adj List for s: a(0) b(0)
 Residual Adj List for a: s(3) b(1) d(3) c(1)
 Residual Adj List for b: s(2) a(0) d(0)
 Residual Adj List for d: a(1) b(2) t(0)
 Residual Adj List for c: a(2) t(0)
 Residual Adj List for t: d(3) c(2)

 ------------------------
 Flow Adj List for s: a(3) b(2)
 Flow Adj List for a: b(0) d(1) c(2)
 Flow Adj List for b: d(2)
 Flow Adj List for d: t(3)
 Flow Adj List for c: t(2)
 Flow Adj List for t:

 ------------------------
 Residual Adj List for b: s(0) d(2)
 Residual Adj List for t: c(0) s(0) d(0)
 Residual Adj List for c: t(1) a(0)
 Residual Adj List for s: b(2) t(4) a(1)
 Residual Adj List for a: c(1) s(0)
 Residual Adj List for d: b(0) t(2)

 ------------------------
 Flow Adj List for b: d(0)
 Flow Adj List for t:
 Flow Adj List for c: t(0)
 Flow Adj List for s: b(0) t(0) a(0)
 Flow Adj List for a: c(0)
 Flow Adj List for d: t(0)

 Final flow: 7
 ------------------------
 Residual Adj List for b: s(2) d(0)
 Residual Adj List for t: c(1) s(4) d(2)
 Residual Adj List for c: t(0) a(1)
 Residual Adj List for s: b(0) t(0) a(0)
 Residual Adj List for a: c(0) s(1)
 Residual Adj List for d: b(2) t(0)

 ------------------------
 Flow Adj List for b: d(2)
 Flow Adj List for t:
 Flow Adj List for c: t(1)
 Flow Adj List for s: b(2) t(4) a(1)
 Flow Adj List for a: c(1)
 Flow Adj List for d: t(2)

 Program ended with exit code: 0
 */
