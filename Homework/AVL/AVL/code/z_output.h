#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// Run:
//---------------------------------------------------------------------
: r
: r
: r
: r
: r
: r
: i
: 10
: i
: 20
: i
: 30
: i 
: 100
: i
: 1000
: i
: 72
: s
: 945
: s
: 478
: s
: 100
: s
: 2
: s
: 90
: s
: 25
: e
: 1000
: e
: 100
: e
: 30
: e
: 20
: e
: 10
: e
: 945
: c
: x
------------ RESULTS --------------------
[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: r
Insert: 945

{945}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: r
Insert: 478

{945}

     {478}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: r
Insert: 892

     {945}

{892}

     {478}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: r
Insert: 492

     {945}

{892}

          {492}

     {478}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: r
Insert: 62

     {945}

{892}

          {492}

     {478}

          {62}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: r
Insert: 224

          {945}

     {892}

          {492}

{478}

          {224}

     {62}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: i
Insert: 10


          {945}

     {892}

          {492}

{478}

          {224}

     {62}

          {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: i
Insert: 20


          {945}

     {892}

          {492}

{478}

          {224}

     {62}

               {20}

          {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: i
Insert: 30


          {945}

     {892}

          {492}

{478}

          {224}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: i
Insert: 100


          {945}

     {892}

          {492}

{478}

          {224}

               {100}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: i
Insert: 1000


               {1000}

          {945}

     {892}

          {492}

{478}

          {224}

               {100}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: i
Insert: 72


               {1000}

          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: s
Search: 945

Item is found.

               {1000}

          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: s
Search: 478

Item is found.

               {1000}

          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: s
Search: 100

Item is found.

               {1000}

          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: s
Search: 2

Item is not found.

               {1000}

          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: s
Search: 90

Item is not found.

               {1000}

          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: s
Search: 25

Item is not found.

               {1000}

          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: e
Erase: 1000


          {945}

     {892}

          {492}

{478}

               {224}

          {100}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: e
Erase: 100


          {945}

     {892}

          {492}

{478}

          {224}

               {72}

     {62}

               {30}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: e
Erase: 30


          {945}

     {892}

          {492}

{478}

          {224}

               {72}

     {62}

          {20}

               {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: e
Erase: 20


          {945}

     {892}

          {492}

{478}

          {224}

               {72}

     {62}

          {10}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: e
Erase: 10


          {945}

     {892}

          {492}

{478}

          {224}

     {72}

          {62}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: e
Erase: 945


     {892}

          {492}

{478}

          {224}

     {72}

          {62}

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: c
Tree is empty

[R]andom [I]nsert [C]lear [S]earch [E]rase E[x]it: x


*/
#endif // Z_OUTPUT_H