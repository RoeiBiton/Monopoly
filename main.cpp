#include <QCoreApplication>
#include<QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <vector>
#include "game.hpp"
#include "player.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::vector<Player> players;

    bool ok;
    int playerCount = QInputDialog::getInt(nullptr, "Number of Players",
                                           "Enter number of players (1-4):",
                                           2, 1, 4, 1, &ok); // Default to 2 players

    if (ok) {
        for (int i = 0; i < playerCount; ++i) {
            QString playerName = QInputDialog::getText(nullptr, "Player Name",
                                                       "Enter name for Player " + QString::number(i + 1) + ":",
                                                       QLineEdit::Normal,
                                                       "Player " + QString::number(i + 1), &ok);
            if (ok && !playerName.isEmpty()) {
                players.emplace_back(playerName.toStdString(), i + 1, i + 1); // ID and logo can be the same for simplicity
            } else {
                QMessageBox::warning(nullptr, "Invalid Input", "Player name cannot be empty.");
                --i; // Retry the same player index
            }
        }

        Game game(players);
        game.startGame(); // Start the game
    } else {
        QMessageBox::warning(nullptr, "Operation Cancelled", "Game setup was cancelled.");
    }

    return a.exec();
}
