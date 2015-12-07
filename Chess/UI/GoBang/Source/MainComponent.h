/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../GoBangBoard.hpp"
#include "../../../Player.hpp"
#include "../../../GameControl.hpp"
#include "../../../CommonUtils.h"

// board config
namespace {
    const int BOARD_WIDTH = 600;
    const int BOARD_HEIGHT = 600;
    const int EDGE_SPACE = 15;
    const int PIECE_RADIUS = 8;
}

struct stPiece {
    float x;
    float y;
    PieceEnum piece;
    stPiece(float x, float y, PieceEnum p) {
        this->x = x;
        this->y = y;
        this->piece = p;
    }
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void configChildComponents();
    void mouseDown(const MouseEvent& event) override;

    void paint (Graphics&);
    void resized();
    void drawBoard(Graphics& g);
    void drawPieces(Graphics& g);
    void insertPiece(PieceEnum piece, float x, float y);
    void cleanBoard();

    void handlePlacePieceResult(PieceEnum piece, int result, int currentPieceX, int currentPieceY);

    bool checkFivePiecesALine(PieceEnum piece, int piecex, int piecey);

    float getSpaceBetweenPieces();

    void startNewGame();

protected:
    void onBoardClicked(const MouseEvent& event);
    void onSaveBoardButtonClicked(const MouseEvent& event);
    
private:
    bool mWhitePieceFirst;
    std::vector<stPiece> mPiecesPoints;
    GameControl mGameControl;

    TextButton mNewGameTextButton;
    TextButton mSaveBoardTextButton;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
