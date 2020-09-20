#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// R1:
//---------------------------------------------------------------------
Inputs: 1, 4
------------ RESULTS --------------------
This was written by call number 1
This was written by call number 2
This was written by call number 3
This was written by call number 4
This was ALSO written by call number 4
This was ALSO written by call number 3
This was ALSO written by call number 2
This was ALSO written by call number 1


//---------------------------------------------------------------------
// R2:
//---------------------------------------------------------------------
Inputs: "BOX", 3
------------ RESULTS --------------------
BOX:1.1.1
BOX:1.1.2
BOX:1.1.3
BOX:1.1.4
BOX:1.1.5
BOX:1.1.6
BOX:1.1.7
BOX:1.1.8
BOX:1.1.9
BOX:1.2.1
BOX:1.2.2
BOX:1.2.3
BOX:1.2.4
BOX:1.2.5
BOX:1.2.6
BOX:1.2.7
BOX:1.2.8
BOX:1.2.9
BOX:1.3.1
BOX:1.3.2
BOX:1.3.3
BOX:1.3.4
BOX:1.3.5
BOX:1.3.6
BOX:1.3.7
BOX:1.3.8
BOX:1.3.9
BOX:1.4.1
BOX:1.4.2
BOX:1.4.3
BOX:1.4.4
BOX:1.4.5
BOX:1.4.6
BOX:1.4.7
BOX:1.4.8
BOX:1.4.9
BOX:1.5.1
BOX:1.5.2
BOX:1.5.3
BOX:1.5.4
BOX:1.5.5
BOX:1.5.6
BOX:1.5.7
BOX:1.5.8
BOX:1.5.9
BOX:1.6.1
BOX:1.6.2
BOX:1.6.3
BOX:1.6.4
BOX:1.6.5
BOX:1.6.6
BOX:1.6.7
BOX:1.6.8
BOX:1.6.9
BOX:1.7.1
BOX:1.7.2
BOX:1.7.3
BOX:1.7.4
BOX:1.7.5
BOX:1.7.6
BOX:1.7.7
BOX:1.7.8
BOX:1.7.9
BOX:1.8.1
BOX:1.8.2
BOX:1.8.3
BOX:1.8.4
BOX:1.8.5
BOX:1.8.6
BOX:1.8.7
BOX:1.8.8
BOX:1.8.9
BOX:1.9.1
BOX:1.9.2
BOX:1.9.3
BOX:1.9.4
BOX:1.9.5
BOX:1.9.6
BOX:1.9.7
BOX:1.9.8
BOX:1.9.9
BOX:2.1.1
BOX:2.1.2
BOX:2.1.3
BOX:2.1.4
BOX:2.1.5
BOX:2.1.6
BOX:2.1.7
BOX:2.1.8
BOX:2.1.9
BOX:2.2.1
BOX:2.2.2
BOX:2.2.3
BOX:2.2.4
BOX:2.2.5
BOX:2.2.6
BOX:2.2.7
BOX:2.2.8
BOX:2.2.9
BOX:2.3.1
BOX:2.3.2
BOX:2.3.3
BOX:2.3.4
BOX:2.3.5
BOX:2.3.6
BOX:2.3.7
BOX:2.3.8
BOX:2.3.9
BOX:2.4.1
BOX:2.4.2
BOX:2.4.3
BOX:2.4.4
BOX:2.4.5
BOX:2.4.6
BOX:2.4.7
BOX:2.4.8
BOX:2.4.9
BOX:2.5.1
BOX:2.5.2
BOX:2.5.3
BOX:2.5.4
BOX:2.5.5
BOX:2.5.6
BOX:2.5.7
BOX:2.5.8
BOX:2.5.9
BOX:2.6.1
BOX:2.6.2
BOX:2.6.3
BOX:2.6.4
BOX:2.6.5
BOX:2.6.6
BOX:2.6.7
BOX:2.6.8
BOX:2.6.9
BOX:2.7.1
BOX:2.7.2
BOX:2.7.3
BOX:2.7.4
BOX:2.7.5
BOX:2.7.6
BOX:2.7.7
BOX:2.7.8
BOX:2.7.9
BOX:2.8.1
BOX:2.8.2
BOX:2.8.3
BOX:2.8.4
BOX:2.8.5
BOX:2.8.6
BOX:2.8.7
BOX:2.8.8
BOX:2.8.9
BOX:2.9.1
BOX:2.9.2
BOX:2.9.3
BOX:2.9.4
BOX:2.9.5
BOX:2.9.6
BOX:2.9.7
BOX:2.9.8
BOX:2.9.9
BOX:3.1.1
BOX:3.1.2
BOX:3.1.3
BOX:3.1.4
BOX:3.1.5
BOX:3.1.6
BOX:3.1.7
BOX:3.1.8
BOX:3.1.9
BOX:3.2.1
BOX:3.2.2
BOX:3.2.3
BOX:3.2.4
BOX:3.2.5
BOX:3.2.6
BOX:3.2.7
BOX:3.2.8
BOX:3.2.9
BOX:3.3.1
BOX:3.3.2
BOX:3.3.3
BOX:3.3.4
BOX:3.3.5
BOX:3.3.6
BOX:3.3.7
BOX:3.3.8
BOX:3.3.9
BOX:3.4.1
BOX:3.4.2
BOX:3.4.3
BOX:3.4.4
BOX:3.4.5
BOX:3.4.6
BOX:3.4.7
BOX:3.4.8
BOX:3.4.9
BOX:3.5.1
BOX:3.5.2
BOX:3.5.3
BOX:3.5.4
BOX:3.5.5
BOX:3.5.6
BOX:3.5.7
BOX:3.5.8
BOX:3.5.9
BOX:3.6.1
BOX:3.6.2
BOX:3.6.3
BOX:3.6.4
BOX:3.6.5
BOX:3.6.6
BOX:3.6.7
BOX:3.6.8
BOX:3.6.9
BOX:3.7.1
BOX:3.7.2
BOX:3.7.3
BOX:3.7.4
BOX:3.7.5
BOX:3.7.6
BOX:3.7.7
BOX:3.7.8
BOX:3.7.9
BOX:3.8.1
BOX:3.8.2
BOX:3.8.3
BOX:3.8.4
BOX:3.8.5
BOX:3.8.6
BOX:3.8.7
BOX:3.8.8
BOX:3.8.9
BOX:3.9.1
BOX:3.9.2
BOX:3.9.3
BOX:3.9.4
BOX:3.9.5
BOX:3.9.6
BOX:3.9.7
BOX:3.9.8
BOX:3.9.9
BOX:4.1.1
BOX:4.1.2
BOX:4.1.3
BOX:4.1.4
BOX:4.1.5
BOX:4.1.6
BOX:4.1.7
BOX:4.1.8
BOX:4.1.9
BOX:4.2.1
BOX:4.2.2
BOX:4.2.3
BOX:4.2.4
BOX:4.2.5
BOX:4.2.6
BOX:4.2.7
BOX:4.2.8
BOX:4.2.9
BOX:4.3.1
BOX:4.3.2
BOX:4.3.3
BOX:4.3.4
BOX:4.3.5
BOX:4.3.6
BOX:4.3.7
BOX:4.3.8
BOX:4.3.9
BOX:4.4.1
BOX:4.4.2
BOX:4.4.3
BOX:4.4.4
BOX:4.4.5
BOX:4.4.6
BOX:4.4.7
BOX:4.4.8
BOX:4.4.9
BOX:4.5.1
BOX:4.5.2
BOX:4.5.3
BOX:4.5.4
BOX:4.5.5
BOX:4.5.6
BOX:4.5.7
BOX:4.5.8
BOX:4.5.9
BOX:4.6.1
BOX:4.6.2
BOX:4.6.3
BOX:4.6.4
BOX:4.6.5
BOX:4.6.6
BOX:4.6.7
BOX:4.6.8
BOX:4.6.9
BOX:4.7.1
BOX:4.7.2
BOX:4.7.3
BOX:4.7.4
BOX:4.7.5
BOX:4.7.6
BOX:4.7.7
BOX:4.7.8
BOX:4.7.9
BOX:4.8.1
BOX:4.8.2
BOX:4.8.3
BOX:4.8.4
BOX:4.8.5
BOX:4.8.6
BOX:4.8.7
BOX:4.8.8
BOX:4.8.9
BOX:4.9.1
BOX:4.9.2
BOX:4.9.3
BOX:4.9.4
BOX:4.9.5
BOX:4.9.6
BOX:4.9.7
BOX:4.9.8
BOX:4.9.9
BOX:5.1.1
BOX:5.1.2
BOX:5.1.3
BOX:5.1.4
BOX:5.1.5
BOX:5.1.6
BOX:5.1.7
BOX:5.1.8
BOX:5.1.9
BOX:5.2.1
BOX:5.2.2
BOX:5.2.3
BOX:5.2.4
BOX:5.2.5
BOX:5.2.6
BOX:5.2.7
BOX:5.2.8
BOX:5.2.9
BOX:5.3.1
BOX:5.3.2
BOX:5.3.3
BOX:5.3.4
BOX:5.3.5
BOX:5.3.6
BOX:5.3.7
BOX:5.3.8
BOX:5.3.9
BOX:5.4.1
BOX:5.4.2
BOX:5.4.3
BOX:5.4.4
BOX:5.4.5
BOX:5.4.6
BOX:5.4.7
BOX:5.4.8
BOX:5.4.9
BOX:5.5.1
BOX:5.5.2
BOX:5.5.3
BOX:5.5.4
BOX:5.5.5
BOX:5.5.6
BOX:5.5.7
BOX:5.5.8
BOX:5.5.9
BOX:5.6.1
BOX:5.6.2
BOX:5.6.3
BOX:5.6.4
BOX:5.6.5
BOX:5.6.6
BOX:5.6.7
BOX:5.6.8
BOX:5.6.9
BOX:5.7.1
BOX:5.7.2
BOX:5.7.3
BOX:5.7.4
BOX:5.7.5
BOX:5.7.6
BOX:5.7.7
BOX:5.7.8
BOX:5.7.9
BOX:5.8.1
BOX:5.8.2
BOX:5.8.3
BOX:5.8.4
BOX:5.8.5
BOX:5.8.6
BOX:5.8.7
BOX:5.8.8
BOX:5.8.9
BOX:5.9.1
BOX:5.9.2
BOX:5.9.3
BOX:5.9.4
BOX:5.9.5
BOX:5.9.6
BOX:5.9.7
BOX:5.9.8
BOX:5.9.9
BOX:6.1.1
BOX:6.1.2
BOX:6.1.3
BOX:6.1.4
BOX:6.1.5
BOX:6.1.6
BOX:6.1.7
BOX:6.1.8
BOX:6.1.9
BOX:6.2.1
BOX:6.2.2
BOX:6.2.3
BOX:6.2.4
BOX:6.2.5
BOX:6.2.6
BOX:6.2.7
BOX:6.2.8
BOX:6.2.9
BOX:6.3.1
BOX:6.3.2
BOX:6.3.3
BOX:6.3.4
BOX:6.3.5
BOX:6.3.6
BOX:6.3.7
BOX:6.3.8
BOX:6.3.9
BOX:6.4.1
BOX:6.4.2
BOX:6.4.3
BOX:6.4.4
BOX:6.4.5
BOX:6.4.6
BOX:6.4.7
BOX:6.4.8
BOX:6.4.9
BOX:6.5.1
BOX:6.5.2
BOX:6.5.3
BOX:6.5.4
BOX:6.5.5
BOX:6.5.6
BOX:6.5.7
BOX:6.5.8
BOX:6.5.9
BOX:6.6.1
BOX:6.6.2
BOX:6.6.3
BOX:6.6.4
BOX:6.6.5
BOX:6.6.6
BOX:6.6.7
BOX:6.6.8
BOX:6.6.9
BOX:6.7.1
BOX:6.7.2
BOX:6.7.3
BOX:6.7.4
BOX:6.7.5
BOX:6.7.6
BOX:6.7.7
BOX:6.7.8
BOX:6.7.9
BOX:6.8.1
BOX:6.8.2
BOX:6.8.3
BOX:6.8.4
BOX:6.8.5
BOX:6.8.6
BOX:6.8.7
BOX:6.8.8
BOX:6.8.9
BOX:6.9.1
BOX:6.9.2
BOX:6.9.3
BOX:6.9.4
BOX:6.9.5
BOX:6.9.6
BOX:6.9.7
BOX:6.9.8
BOX:6.9.9
BOX:7.1.1
BOX:7.1.2
BOX:7.1.3
BOX:7.1.4
BOX:7.1.5
BOX:7.1.6
BOX:7.1.7
BOX:7.1.8
BOX:7.1.9
BOX:7.2.1
BOX:7.2.2
BOX:7.2.3
BOX:7.2.4
BOX:7.2.5
BOX:7.2.6
BOX:7.2.7
BOX:7.2.8
BOX:7.2.9
BOX:7.3.1
BOX:7.3.2
BOX:7.3.3
BOX:7.3.4
BOX:7.3.5
BOX:7.3.6
BOX:7.3.7
BOX:7.3.8
BOX:7.3.9
BOX:7.4.1
BOX:7.4.2
BOX:7.4.3
BOX:7.4.4
BOX:7.4.5
BOX:7.4.6
BOX:7.4.7
BOX:7.4.8
BOX:7.4.9
BOX:7.5.1
BOX:7.5.2
BOX:7.5.3
BOX:7.5.4
BOX:7.5.5
BOX:7.5.6
BOX:7.5.7
BOX:7.5.8
BOX:7.5.9
BOX:7.6.1
BOX:7.6.2
BOX:7.6.3
BOX:7.6.4
BOX:7.6.5
BOX:7.6.6
BOX:7.6.7
BOX:7.6.8
BOX:7.6.9
BOX:7.7.1
BOX:7.7.2
BOX:7.7.3
BOX:7.7.4
BOX:7.7.5
BOX:7.7.6
BOX:7.7.7
BOX:7.7.8
BOX:7.7.9
BOX:7.8.1
BOX:7.8.2
BOX:7.8.3
BOX:7.8.4
BOX:7.8.5
BOX:7.8.6
BOX:7.8.7
BOX:7.8.8
BOX:7.8.9
BOX:7.9.1
BOX:7.9.2
BOX:7.9.3
BOX:7.9.4
BOX:7.9.5
BOX:7.9.6
BOX:7.9.7
BOX:7.9.8
BOX:7.9.9
BOX:8.1.1
BOX:8.1.2
BOX:8.1.3
BOX:8.1.4
BOX:8.1.5
BOX:8.1.6
BOX:8.1.7
BOX:8.1.8
BOX:8.1.9
BOX:8.2.1
BOX:8.2.2
BOX:8.2.3
BOX:8.2.4
BOX:8.2.5
BOX:8.2.6
BOX:8.2.7
BOX:8.2.8
BOX:8.2.9
BOX:8.3.1
BOX:8.3.2
BOX:8.3.3
BOX:8.3.4
BOX:8.3.5
BOX:8.3.6
BOX:8.3.7
BOX:8.3.8
BOX:8.3.9
BOX:8.4.1
BOX:8.4.2
BOX:8.4.3
BOX:8.4.4
BOX:8.4.5
BOX:8.4.6
BOX:8.4.7
BOX:8.4.8
BOX:8.4.9
BOX:8.5.1
BOX:8.5.2
BOX:8.5.3
BOX:8.5.4
BOX:8.5.5
BOX:8.5.6
BOX:8.5.7
BOX:8.5.8
BOX:8.5.9
BOX:8.6.1
BOX:8.6.2
BOX:8.6.3
BOX:8.6.4
BOX:8.6.5
BOX:8.6.6
BOX:8.6.7
BOX:8.6.8
BOX:8.6.9
BOX:8.7.1
BOX:8.7.2
BOX:8.7.3
BOX:8.7.4
BOX:8.7.5
BOX:8.7.6
BOX:8.7.7
BOX:8.7.8
BOX:8.7.9
BOX:8.8.1
BOX:8.8.2
BOX:8.8.3
BOX:8.8.4
BOX:8.8.5
BOX:8.8.6
BOX:8.8.7
BOX:8.8.8
BOX:8.8.9
BOX:8.9.1
BOX:8.9.2
BOX:8.9.3
BOX:8.9.4
BOX:8.9.5
BOX:8.9.6
BOX:8.9.7
BOX:8.9.8
BOX:8.9.9
BOX:9.1.1
BOX:9.1.2
BOX:9.1.3
BOX:9.1.4
BOX:9.1.5
BOX:9.1.6
BOX:9.1.7
BOX:9.1.8
BOX:9.1.9
BOX:9.2.1
BOX:9.2.2
BOX:9.2.3
BOX:9.2.4
BOX:9.2.5
BOX:9.2.6
BOX:9.2.7
BOX:9.2.8
BOX:9.2.9
BOX:9.3.1
BOX:9.3.2
BOX:9.3.3
BOX:9.3.4
BOX:9.3.5
BOX:9.3.6
BOX:9.3.7
BOX:9.3.8
BOX:9.3.9
BOX:9.4.1
BOX:9.4.2
BOX:9.4.3
BOX:9.4.4
BOX:9.4.5
BOX:9.4.6
BOX:9.4.7
BOX:9.4.8
BOX:9.4.9
BOX:9.5.1
BOX:9.5.2
BOX:9.5.3
BOX:9.5.4
BOX:9.5.5
BOX:9.5.6
BOX:9.5.7
BOX:9.5.8
BOX:9.5.9
BOX:9.6.1
BOX:9.6.2
BOX:9.6.3
BOX:9.6.4
BOX:9.6.5
BOX:9.6.6
BOX:9.6.7
BOX:9.6.8
BOX:9.6.9
BOX:9.7.1
BOX:9.7.2
BOX:9.7.3
BOX:9.7.4
BOX:9.7.5
BOX:9.7.6
BOX:9.7.7
BOX:9.7.8
BOX:9.7.9
BOX:9.8.1
BOX:9.8.2
BOX:9.8.3
BOX:9.8.4
BOX:9.8.5
BOX:9.8.6
BOX:9.8.7
BOX:9.8.8
BOX:9.8.9
BOX:9.9.1
BOX:9.9.2
BOX:9.9.3
BOX:9.9.4
BOX:9.9.5
BOX:9.9.6
BOX:9.9.7
BOX:9.9.8
BOX:9.9.9


//---------------------------------------------------------------------
// R3:
//---------------------------------------------------------------------
Inputs: "CAT", "MAN"
------------ RESULTS --------------------
TACMAN
ATCMAN
CTAMAN
TCAMAN
ACTMAN
CATMAN


//---------------------------------------------------------------------
// R4:
//---------------------------------------------------------------------
: 3
: 2
: 1
: 0
: 0
: 0
: 0
: 0
: 0
------------ RESULTS --------------------
How many boxes do you see?: 4

You are in box: 1
How many boxes do you see?: 3

You are in box: 1.1
How many boxes do you see?: 2

You are in box: 1.1.1
How many boxes do you see?: 1

You are in box: 1.1.1.1
How many boxes do you see?: 0

You are in box: 1.1.2
How many boxes do you see?: 0

You are in box: 1.2
How many boxes do you see?: 0

You are in box: 1.3
How many boxes do you see?: 0

You are in box: 2
How many boxes do you see?: 0

You are in box: 3
How many boxes do you see?: 0

You are in box: 4
How many boxes do you see?: 0

Total boxes: 10


//---------------------------------------------------------------------
// R5:
//---------------------------------------------------------------------
Inputs: 3
------------ RESULTS --------------------
1.83333


//---------------------------------------------------------------------
// R16:
//---------------------------------------------------------------------
: n
: l
: n
: l
: n
: l
: n
: h
: n
: h
: y

------------ RESULTS --------------------
Is your number 500000? (y/n): n
Is your number lower or higher than 500000? (l/h): l
Is your number 250000? (y/n): n
Is your number lower or higher than 250000? (l/h): l
Is your number 125000? (y/n): n
Is your number lower or higher than 125000? (l/h): l
Is your number 62500? (y/n): n
Is your number lower or higher than 62500? (l/h): h
Is your number 93750? (y/n): n
Is your number lower or higher than 93750? (l/h): h
Is your number 109375? (y/n): y


*/
#endif // Z_OUTPUT_H