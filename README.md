Monopoly Game in C++ 
Project by: Roei Biton ID:206400426 Roei.biton33@gmail.com
Project Description
This project is a C++ implementation of the classic Monopoly game using the Qt framework for graphical user interface (GUI) representation.
It manages the game's logic, player interactions, and the game board with properties, cards, and dice.

Overview
The project consists of several classes that work together to create the game experience:

1. Game Class: Game
Description: Manages the overall game, including players, the game board, and game mechanics such as turns and property management.
Key Features:
Handles player turns and movements.
Manages property purchases and development.
Processes game events like drawing Chance and Community Chest cards.
Updates GUI components to reflect the game state.

3. Board Class: Board
Description: Represents the game board and manages the properties and card queues.
Key Features:
Stores all properties on the board.
Manages Chance and Community Chest cards.
Provides methods to retrieve properties and draw cards.

5. Player Class: Player
Description: Represents a player in the game.
Key Features:
Manages player attributes like name, money balance, and owned properties.
Provides methods for buying, selling properties, and handling financial transactions.

7. Property Class: Property
Description: Represents a property on the board.
Key Features:
Stores property details, including owner, rent, and development options.
Manages the rent updates based on property development.

9. Dice Class: Dice
Description: Simulates rolling dice for player movement.
Key Features:
Provides a method to roll the dice and return a random value.

11. Card Class: Card
Description: Represents a card in the game, either Chance or Community Chest.
Key Features:
Stores card details like description, value, and type.

GUI Implementation
The game uses Qt for the GUI, which includes graphical representations of the game board, player icons, and property details.
The graphical scene is updated dynamically based on game events and player actions.


Project by: Roei Biton ID:206400426 Roei.biton33@gmail.com
