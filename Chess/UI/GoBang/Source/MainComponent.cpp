/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "ResultComponent.h"
#include "NewGameTextButtonMouseListener.h"
//==============================================================================
MainContentComponent::MainContentComponent() : mNewGameTextButton("New Game", "End this game, and begin a new battle."),
                                               mSaveBoardTextButton("Save Game", "Save game"),
                                               mLoadBoardTextButton("Load Game", "Load a game from local file.")
{
    setSize (BOARD_WIDTH + 150, BOARD_HEIGHT);
    
    addChildComponent(&mNewGameTextButton);
    addChildComponent(&mSaveBoardTextButton);
    addChildComponent(&mLoadBoardTextButton);
    configChildComponents();
    
    mWhitePieceFirst = true;
}

void MainContentComponent::configChildComponents() {
    mNewGameTextButton.setTopRightPosition(650, 15);
    mNewGameTextButton.setVisible(true);
    mNewGameTextButton.setSize(80, 50);
    mNewGameTextButton.addMouseListener(new NewGameTextButtonMouseListener(this), true);

    mSaveBoardTextButton.setTopRightPosition(650, 75);
    mSaveBoardTextButton.setVisible(true);
    mSaveBoardTextButton.setSize(80, 50);
    mSaveBoardTextButton.addMouseListener(this, true);

    mLoadBoardTextButton.setTopRightPosition(650, 135);
    mLoadBoardTextButton.setVisible(true);
    mLoadBoardTextButton.setSize(80, 50);
    mLoadBoardTextButton.addMouseListener(this, true);
}

MainContentComponent::~MainContentComponent()
{
}

float MainContentComponent::getSpaceBetweenPieces() {
    float hspaceBetweenPieces = 1.0f * (BOARD_WIDTH - EDGE_SPACE * 2) / (CHESS_COLUMN_COUNT -1);
    return hspaceBetweenPieces;
}

void MainContentComponent::mouseDown(const MouseEvent& event) {

    std::cout << std::hex << event.originalComponent;

    if (event.originalComponent == &mSaveBoardTextButton) {
        std::cout << "Click saveBoardTextButton" << std::endl;
        onSaveBoardButtonClicked(event);
    } else if (event.originalComponent == &mLoadBoardTextButton) {
        std::cout << "Click LoadBoardTextButton" << std::endl;
        onLoadBoardButtonClicked(event);
    } else {
        onBoardClicked(event);
    } // else

}

void MainContentComponent::onSaveBoardButtonClicked(const MouseEvent& event) {
    CommonUtils::SaveBoard(mGameControl.GetBoard(), "./board_2015_12_07.txt");
}

/** 
 * 
 * 
 * @param event 
 */
void MainContentComponent::onLoadBoardButtonClicked(const MouseEvent& event) {
    int flags = FileBrowserComponent::FileChooserFlags::filenameBoxIsReadOnly | FileBrowserComponent::FileChooserFlags::saveMode | FileBrowserComponent::FileChooserFlags::canSelectFiles;
    FileBrowserComponent *fileBrowser = new FileBrowserComponent(flags , File::nonexistent, nullptr, nullptr); 
    fileBrowser->setSize(300, 300);
    FileFilter* ff = new WildcardFileFilter("*.txt", "", "");
    fileBrowser->setFileFilter(ff);
    DialogWindow::showModalDialog("Open File", fileBrowser, this, Colours::white, true);
    std::cout << "numSelectedFiles: " << fileBrowser->getNumSelectedFiles() << std::endl;
    if (fileBrowser->getNumSelectedFiles() > 0) {
        File file = fileBrowser->getSelectedFile(0);
        std::cout << "SelectedFileName: " << file.getFileName() << std::endl;
        GoBangBoard board = CommonUtils::LoadBoard(file.getFileName().toStdString()) ;

        board.PrintBoard();
        
        mGameControl.SetBoard(board);

        mPiecesPoints.clear();
        int viewX = 0;
        int viewY = 0;

        for (int i = 0; i < CHESS_COLUMN_COUNT; i++) {
            for (int j = 0; j < CHESS_ROW_COUNT; j++) {
                int value = mGameControl.GetBoard().GetPieceValue(i, j);
                if (value == mGameControl.GetBoard().GetChessValue(WHITE_PIECE)) {
                    mWhitePieceFirst = true;
                    convertLogicXY2ViewXY(i, j, viewX, viewY);
                    insertPiece(WHITE_PIECE, viewX, viewY);
                    std::cout << "(i,j) : " << i << ", " << j << " white"<< std::endl;
                } 

                if (value == mGameControl.GetBoard().GetChessValue(BLACK_PIECE)) {
                    mWhitePieceFirst = false;
                    convertLogicXY2ViewXY(i, j, viewX, viewY);
                    insertPiece(BLACK_PIECE, viewX, viewY);
                    std::cout << "(i,j) : " << i << ", " << j << " black"<< std::endl;
                } 
            }
        }
        mWhitePieceFirst = !mWhitePieceFirst;
        repaint();
    }
    delete fileBrowser;
    delete ff;
}

void MainContentComponent::onBoardClicked(const MouseEvent& event) {
    int x = event.getMouseDownX();
    int y = event.getMouseDownY();
    
    float hspaceBetweenPieces = getSpaceBetweenPieces();
    int boardy = std::floor((x - EDGE_SPACE + hspaceBetweenPieces / 2.0f) / hspaceBetweenPieces);
    int boardx = std::floor((y - EDGE_SPACE + hspaceBetweenPieces / 2.0f) / hspaceBetweenPieces);

    int result = 0;
    if (mWhitePieceFirst) {
        // x: 行 y: 列
        result = mGameControl.PlacePiece(WHITE_PIECE, boardx, boardy);  // 
        handlePlacePieceResult(WHITE_PIECE, result, boardx, boardy);
    } else {
        result = mGameControl.PlacePiece(BLACK_PIECE, boardx, boardy);
        handlePlacePieceResult(BLACK_PIECE, result, boardx, boardy);
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
    float viewY = currentPieceX * hspaceBetweenPieces + EDGE_SPACE - PIECE_RADIUS;
    float viewX = currentPieceY * hspaceBetweenPieces + EDGE_SPACE - PIECE_RADIUS;
    insertPiece(piece, viewX, viewY);

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

void MainContentComponent::convertLogicXY2ViewXY(int logicx, int logicy, int& viewx, int& viewy) {
    float hspaceBetweenPieces = getSpaceBetweenPieces();
    float pieceY = logicx * hspaceBetweenPieces + EDGE_SPACE - PIECE_RADIUS;
    float pieceX = logicy * hspaceBetweenPieces + EDGE_SPACE - PIECE_RADIUS;
    viewx = pieceX;
    viewy = pieceY;
}
