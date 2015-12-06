/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "ResultComponent.h"
#include "NewGameTextButtonMouseListener.h"
//==============================================================================
MainContentComponent::MainContentComponent() : mNewGameTextButton("New Game", "End this game, and begin a new battle.")
{
    setSize (BOARD_WIDTH + 150, BOARD_HEIGHT);
    
    addChildComponent(&mNewGameTextButton);
    configChildComponents();
    
    mWhitePieceFirst = true;
}

void MainContentComponent::configChildComponents() {
    mNewGameTextButton.setTopRightPosition(650, 15);
    mNewGameTextButton.setVisible(true);
    mNewGameTextButton.setSize(80, 50);
    mNewGameTextButton.addMouseListener(new NewGameTextButtonMouseListener(this), true);
}

MainContentComponent::~MainContentComponent()
{
}

float MainContentComponent::getSpaceBetweenPieces() {
    float hspaceBetweenPieces = 1.0f * (BOARD_WIDTH - EDGE_SPACE * 2) / (CHESS_COLUMN_COUNT -1);
    return hspaceBetweenPieces;
}

void MainContentComponent::mouseDown(const MouseEvent& event) {
    int x = event.getMouseDownX();
    int y = event.getMouseDownY();
    
    float hspaceBetweenPieces = getSpaceBetweenPieces();
    int v = std::floor((x - EDGE_SPACE + hspaceBetweenPieces / 2.0f) / hspaceBetweenPieces);
    int h = std::floor((y - EDGE_SPACE + hspaceBetweenPieces / 2.0f) / hspaceBetweenPieces);

    int result = 0;
    if (mWhitePieceFirst) {
        // x: 行 y: 列
        result = mGameControl.PlacePiece(WHITE_PIECE, v, h);
        handlePlacePieceResult(WHITE_PIECE, result, v, h);
    } else {
        result = mGameControl.PlacePiece(BLACK_PIECE, v, h);
        handlePlacePieceResult(BLACK_PIECE, result, v, h);
    }


}

void MainContentComponent::paint (Graphics& g)
{
    drawBoard(g);
    drawPieces(g);
}


void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::drawBoard(Graphics& g) {
    g.fillAll (Colours::grey);

    g.setFont (Font (16.0f));
    g.setColour (Colours::yellow);

    // 画棋盘
    for (int i = 0; i < CHESS_ROW_COUNT; i++) {
        // 画横线
        float hspaceBetweenPieces = 1.0f * (BOARD_WIDTH - EDGE_SPACE * 2) / (CHESS_COLUMN_COUNT -1);
        float startx = EDGE_SPACE;
        float starty = EDGE_SPACE + hspaceBetweenPieces * i;
        float endx = BOARD_WIDTH - EDGE_SPACE;
        float endy = starty;
        g.drawLine(startx, starty, endx, endy, 2);

        //画竖线
        float vspaceBetweenPieces = 1.0f * (BOARD_HEIGHT - EDGE_SPACE * 2) / (CHESS_ROW_COUNT - 1);
        startx = EDGE_SPACE + vspaceBetweenPieces * i;
        starty = EDGE_SPACE;
        endx = startx;
        endy = BOARD_HEIGHT - EDGE_SPACE;
        g.drawLine(startx, starty, endx, endy, 2);
    }

}

void MainContentComponent::drawPieces(Graphics& g) {
    std::vector<stPiece>::iterator itNext = mPiecesPoints.begin();
    std::vector<stPiece>::iterator itEnd = mPiecesPoints.end();
    for (; itNext != itEnd; itNext++) {
        if (itNext->piece == WHITE_PIECE) {
            g.setColour(Colours::white);
        } else {
            g.setColour(Colours::black);
        }
        g.fillEllipse(itNext->x, itNext->y, 2 * PIECE_RADIUS, 2 * PIECE_RADIUS);
    }
}

void MainContentComponent::insertPiece(PieceEnum piece, float x, float y) {
    mPiecesPoints.push_back(stPiece(x, y, piece));
    repaint();
}


void MainContentComponent::cleanBoard() {
    mGameControl.GetBoard().ClearBoard();
    mPiecesPoints.clear();
    repaint();
}

void MainContentComponent::handlePlacePieceResult(PieceEnum piece, int result, int currentPieceX, int currentPieceY) {
    // error code handle
    if (result == -1) {
        std::cerr << "棋子位置被占用!" << std::endl;
        auto* p = new ResultContentComponent("Invalid Position");
        DialogWindow::showModalDialog("Result", p, this, Colours::yellow, true);
        delete p;
        return;
    }
        
    if (result == -2) {
        std::cerr << "棋子超出棋盘边界!" << std::endl;
        return;
    }

    float hspaceBetweenPieces = getSpaceBetweenPieces();
    float pieceX = currentPieceX * hspaceBetweenPieces + EDGE_SPACE - PIECE_RADIUS;
    float pieceY = currentPieceY * hspaceBetweenPieces + EDGE_SPACE - PIECE_RADIUS;
    insertPiece(piece, pieceX, pieceY);

    if (checkFivePiecesALine(piece, currentPieceX, currentPieceY)) {
        mGameControl.GetBoard().PrintBoard();
        // pop up dialog
        std::string message("White Player Win!");
        if (piece == BLACK_PIECE) {
            message = "Black Player Win!";
        }
        auto *p = new ResultContentComponent(message);
        int dialogCode = DialogWindow::showModalDialog("Result", p, this, Colours::white, true);
        delete p;
            
        std::cout << "dialog return code: " << dialogCode << std::endl;
        return;
    }

    if (mGameControl.GetBoard().IsBoardFull()) {
        std::cout << "平局！" << std::endl;

        mGameControl.GetBoard().PrintBoard();
        // pop up dialog
        int dialogCode = DialogWindow::showModalDialog("Result", this, this, Colours::yellow, true);
        std::cout << "dialog return code: " << dialogCode << std::endl;
        return;
    }
        
    mWhitePieceFirst = !mWhitePieceFirst;
}


bool MainContentComponent::checkFivePiecesALine(PieceEnum piece, int piecex, int piecey) {
    if (mGameControl.GetBoard().InFiveChessLine(piece, piecex, piecey)) {
        return true;
    }

    return false;
}


void MainContentComponent::startNewGame() {
    mPiecesPoints.clear();
    mWhitePieceFirst = true;
    mGameControl.StartNewGame();
    
    repaint();
}
