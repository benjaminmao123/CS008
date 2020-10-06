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
[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 929

{929}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 713

{929}

     {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 464

     {464}

{929}

     {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 787

     {464}

{929}

     {787}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 67

     {464}

{929}

          {67}

     {787}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 813

     {813}

          {464}

{929}

          {67}

     {787}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 865

          {813}

     {865}

          {464}

{929}

          {67}

     {787}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 374

          {813}

     {865}

          {464}

{929}

          {67}

     {787}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 375

          {813}

     {865}

          {464}

{929}

          {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 159

          {813}

     {865}

          {464}

{929}

          {159}

               {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 654

          {813}

     {865}

          {464}

{929}

               {159}

          {654}

               {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 58

          {813}

     {865}

          {464}

               {58}

{929}

               {159}

          {654}

               {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 192

          {813}

     {865}

               {192}

          {464}

               {58}

{929}

               {159}

          {654}

               {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 352

          {813}

               {352}

     {865}

               {192}

          {464}

               {58}

{929}

               {159}

          {654}

               {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: r
Insert: 415

               {415}

          {813}

               {352}

     {865}

               {192}

          {464}

               {58}

{929}

               {159}

          {654}

               {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 415

          {813}

               {352}

     {415}

               {192}

          {464}

               {58}

{865}

               {159}

          {654}

               {67}

     {787}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 352

          {813}

     {415}

               {192}

          {464}

               {58}

{787}

               {159}

          {654}

               {67}

     {352}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 192

          {813}

     {192}

          {464}

               {58}

{415}

               {159}

          {654}

               {67}

     {352}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 58

          {813}

     {192}

          {464}

{352}

               {159}

          {654}

               {67}

     {58}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 159

          {813}

     {159}

          {464}

{192}

          {654}

               {67}

     {58}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: pp
Pop: 67

          {813}

     {67}

          {464}

{159}

          {654}

     {58}

               {375}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: Pop: 375

          {813}

     {67}

          {464}

{375}

          {654}

     {58}

          {713}

               {374}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 374

          {813}

     {67}

          {464}

{374}

          {654}

     {58}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 813

     {67}

          {464}

{813}

          {654}

     {58}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 464

     {67}

{464}

          {654}

     {58}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 654

     {67}

{654}

     {58}

          {713}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 713

     {67}

{713}

     {58}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 67

{67}

     {58}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 58

{58}

[R]andom [I]nsert [C]lear [P]op E[x]it: p
Pop: 58



*/
#endif // Z_OUTPUT_H