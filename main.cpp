#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug> // Include QDebug for debugging messages
#include "game.hpp"
#include "player.hpp" // Ensure you have this include for Player class

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create a QGraphicsScene
    QGraphicsScene scene;

    // Ask the user for the number of players
    bool ok;
    int playerCount = QInputDialog::getInt(nullptr, "Number of Players",
                                           "How many players will be playing? (2-8)",
                                           2, 2, 8, 1, &ok); // Default to 2 players

    if (!ok) {
        // User cancelled the dialog
        return 0; // Exit the application
    }

    // Create players based on user input
    std::vector<Player> players;
    for (int i = 0; i < playerCount; ++i) {
        QString playerName = QInputDialog::getText(nullptr, "Player Name",
                                                   "Enter name for Player " + QString::number(i + 1) + ":",
                                                   QLineEdit::Normal, "", &ok);
        if (ok && !playerName.isEmpty()) {
            players.emplace_back(playerName.toStdString(), i); // Use i for player ID and 0 as a placeholder for logo
        } else {
            QMessageBox::warning(nullptr, "Invalid Input", "You must enter a valid name.");
            return 1; // Exit if the input is invalid
        }
    }
    //////////////////////
    /// \brief MAX_LOGO_WIDTH
    ///    // Define the size of the board
    const int BOARD_WIDTH = 800;  // Set your desired board width
    const int BOARD_HEIGHT = 800; // Set your desired board height

    // Create the Game object
    Game game(players, &scene);

    // Set up the QGraphicsView
    QGraphicsView view(&scene);
    view.setFixedSize(BOARD_WIDTH, BOARD_HEIGHT); // Set the desired size for the view
    view.setWindowTitle("Monopoly Game");

    // Load and display the Monopoly board image
    QPixmap boardImage("/Users/roeibiton/QtProjects/Monopoly/monopoly_board.jpg"); // Replace with the path to your board image
    boardImage = boardImage.scaled(BOARD_WIDTH, BOARD_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    scene.addPixmap(boardImage); // Add the board image to the scene

    QGraphicsPixmapItem* boardItem = scene.addPixmap(boardImage);
    boardItem->setZValue(0);
    view.show();

    // Start the game
    game.startGame();

    return app.exec();
}
