A varient of [**Gomoku**](https://en.wikipedia.org/wiki/Gomoku) (Five in a Row) client featuring a powerful AI written in `C++` and `python`.

There are two main components in this project:

  * A strong AI player based on Minimax with α-β pruning, alongside many performance optimisations ([strong_ai](strong_ai))
  * A weak AI player based on Minimax with α-β pruning ([weak_ai/cpp](weak_ai/cpp))
  * A weak AI player based on Minimax with α-β pruning ([weak_ai/python](weak_ai/python))

##  Gomoku Board
  <p aligm="center"><img width="400" height="400" src="board.png"/></p>


## Getting Started
1. Make sure the compiler support C++11.

2. To run the weak ai (baseline):

        $ cd weak_ai/cpp/
        $ make
        $ ./play

   Look at `play.cpp` to get some sense of how to use the library.
3. To run the strong ai:

        $ cd strong_ai/
        $ make
        $./play

   Look at play.cpp to get some sense of how to use the library.

## License
    This AI is released under the [MIT License](https://opensource.org/licenses/MIT).


