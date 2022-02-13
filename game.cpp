#include "game.hpp"

Player::Player() {
    this->currentRoom = nullptr;
}

Room* Player::GetCurrentRoom() {
    return this->currentRoom;
}

void Player::SetCurrentRoom(Room* r) {
    this->currentRoom = r;
}

void Player::Move(Room::Direction dir) {
    this->SetCurrentRoom(this->currentRoom->GetPath(dir));
}

bool Player::TryTakeItem(Item item) {

}

bool Player::TryDropItem(Item item) {

}

vector<Item> Player::GetInv() {
    return this->inventory;
}


const string Game::Messages::Title = "Game Title Will Go Here";
const string Game::Messages::Help = "This is the help message.";
const string Game::Messages::UnknownCommand = "Command not recognized.";
const string Game::Messages::UnknownDirection = "Which way do you want to go?";
const string Game::Messages::BlockedDirection = "You can't go that way!";

Game::Game(string winTitle, int winWidth, int winHeight)
    : textbox(0, winHeight-100, winWidth, 100, [&](string s) { this->EvalText(s); }) {
    this->winTitle = winTitle;
    this->winWidth = winWidth;
    this->winHeight = winHeight;
    this->state = GameState::Title;
    this->textbox.SetGameText(Game::Messages::Title);
}

/* initializes the game and window */
void Game::Init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(this->winWidth, this->winHeight, this->winTitle.c_str());
    SetExitKey(KEY_ESCAPE);
    SetTargetFPS(60);

    // TODO: GameTexture
    Image img = LoadImage("./assets/a.png");
    this->texture = LoadTextureFromImage(img);
    UnloadImage(img);


    // create rooms
    this->rooms.insert({
        { "Kitchen", new Room("Kitchen", Room::Messages {
            .OnEnter = "You have entered the kitchen. ",
            .OnFirstEnter = "You have entered the kitchen. Various pots and pans lay scattered throughout. ",
            .OnStay = "You are in the kitchen. ",
            .OnLook = "You are in the kitchen. Various pots and pans lay scattered throughout, and a red key sits next to the stove. ",
        })},
        { "Bedroom", new Room("Bedroom", Room::Messages {
            .OnEnter = "You have entered the bedroom. ",
            .OnFirstEnter = "You have entered the bedroom. A queen size bed, neatly made, sits in the middle of the room. ",
            .OnStay = "You are in the bedroom. ",
            .OnLook = "You are in the bedroom. Across from the queen-size bed, you see a giant red door. ",
        })},
    });

    // create items

    /*this->items.insert({
        { "Red Key", new Item("Red Key", Item::ItemAttrs {
            .canCarry = true,
            .canUse = true,
        }}),
        { "Red Door", new Item("Red Door", Item::ItemAttrs {
            .canCarry = true,
            .canUse = false,
        }}),
    });
    */
   
    this->items.insert({
        {"Red Key", new Item("Red Key", Item::ItemAttrs {
            .canCarry = true,
            .canUse = true,
        })}
    });

    // link rooms
    this->rooms.at("Kitchen").Link(this->rooms.at("Bedroom"), Room::Direction::North);

    // add items to rooms
    this->rooms.at("Kitchen").AddItem(this->items.at("Red Key"));
    this->rooms.at("Bedroom").AddItem(this->items.at("Red Door"));
}

/* main loop */
void Game::Run() {
    while (!WindowShouldClose()) {
        this->Draw();
    }
}

/* unused for now - maybe impl this when player can die */
void Game::Reset() {}

/* cleans up resources */
void Game::Destroy() {
    UnloadTexture(this->texture);
    CloseWindow();
    delete this;
}

/* main draw function, called in Run */
void Game::Draw() {
    BeginDrawing();

    switch (this->state) {

        case GameState::Title:
        case GameState::Gameplay: {

            DrawTexture(this->texture, 0, 0, WHITE);
            this->textbox.Draw();

            // handle input
            vector<KeyboardKey> keys = Game::GetKeysPressed();
            // keep this this way
            bool shift = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
            for (KeyboardKey& k : keys) {
                this->textbox.AddChar(k, shift);
            }

            break;
        }
        
        default: break;
    }
    
    EndDrawing();
}

/* 
    Contains initialization logic for each state
*/
void Game::SetState(GameState new_state) {

    GameState old_state = this->state;

    // if starting the game
    if (old_state == GameState::Title && new_state == GameState::Gameplay) {
        Room& startingRoom = this->rooms.at("Kitchen");

        this->player.SetCurrentRoom(&startingRoom);
        startingRoom.Visit();
        //this->textbox.SetGameText(startingRoom.GetMessages().OnStay);
        this->textbox.SetGameText("You are in the kitchen. ");
    }

    this->state = new_state;
}

/* Checks player text against each command and executes the onCall if it matches */
void Game::EvalText(string text) {
    for (const Command& c : this->GetCommands()) {
        if (c.IsMatch(text)) {
            c.onMatch();
            break;
        }
    }
}

/* get a list of all keys pressed - used only for the text input */
vector<KeyboardKey> Game::GetKeysPressed(void) {

    // stupid
    // shift not included
    static const int relevantKeys[] = {
        KEY_APOSTROPHE, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH, KEY_ZERO, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR,
        KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, KEY_SEMICOLON, KEY_EQUAL, KEY_A, KEY_B, KEY_C, KEY_D,
        KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S,
        KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_LEFT_BRACKET, KEY_BACKSLASH, KEY_RIGHT_BRACKET, KEY_GRAVE,
        KEY_SPACE, KEY_ENTER, KEY_TAB, KEY_BACKSPACE, KEY_DELETE, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP,
    };

    vector<KeyboardKey> keys;
    KeyboardKey k;

    for (int i = 0; i < (int)(sizeof(relevantKeys) / sizeof(int)); i++) {
        k = (KeyboardKey) relevantKeys[i];
        if (IsKeyPressed(k)) {
            keys.push_back(k);
        }
    }
    return keys;
}

/* get all commands CURRENTLY allowed - like "take x" for each item in inv */
vector<Command> Game::GetCommands() {
    vector<Command> commands;


    // game commands
    if (this->state == GameState::Title) {
        commands.push_back(Command("Start Game", "start( game)?", [&]{ this->SetState(GameState::Gameplay); }));
    }
    commands.push_back(Command("Quit Game", "(q(uit)?)|(exit)( game)?", []{ throw ExitGameException(); }));
    commands.push_back(Command("Help", "help", [&]{ this->textbox.SetGameText(Game::Messages::Help); }));
    commands.push_back(Command("Check Inventory", "(check )?inv(entory)?", [&]{ this->textbox.SetGameText(this->GetPlayerInvAsString()); }));

    // direction commands
    if (this->state == GameState::Gameplay) {
        commands.push_back(Command("Go North", "(go )?n(orth)?", [&]{ this->TryMove(Room::Direction::North); }));
        commands.push_back(Command("Go South", "(go )?s(outh)?", [&]{ this->TryMove(Room::Direction::South); }));
        commands.push_back(Command("Go East", "(go )?e(ast)?", [&]{ this->TryMove(Room::Direction::East); }));
        commands.push_back(Command("Go West", "(go )?w(est)?", [&]{ this->TryMove(Room::Direction::West); }));
    }

    // room commands
    if (this->state == GameState::Gameplay) {
        commands.push_back(Command("Look Around", "look( around)?", [&]{ this->textbox.SetGameText(this->player.GetCurrentRoom()->GetMessages().OnLook); }));
    }

    /* everything else will go here */

    if (this->state == GameState::Gameplay) {
        commands.push_back(Command("Failsafe: Unknown Direction", "go.*", [&]{ this->textbox.SetGameText(Game::Messages::UnknownDirection); }));
    }

    commands.push_back(Command("Failsafe: Unknown Command", ".*", [&]{ this->textbox.SetGameText(Game::Messages::UnknownCommand); }));
    return commands;

}

/* performs the failure check */
void Game::TryMove(Room::Direction dir) {
    Room *r = this->player.GetCurrentRoom()->GetPath(dir);
    if (r == nullptr) {
        this->textbox.SetGameText(Game::Messages::BlockedDirection);
    } else {
        this->player.Move(dir);
        this->textbox.SetGameText("You went " + Room::DirToString[dir] + ".\n" + this->player.GetCurrentRoom()->GetEnterMsg());
        this->player.GetCurrentRoom()->Visit();
    }
}

/* string representation of inventory */
std::string Game::GetPlayerInvAsString() {
    vector<Item> inv = this->player.GetInv();
    switch (inv.size()) {
        case 0: return "Your inventory is empty.";
        case 1: return "Your inventory contains " + inv.at(0).repr() + ".";
        case 2: return "Your inventory contains " + inv.at(0).repr() + " and " + inv.at(1).repr() + ".";
        case 3: return "Your inventory contains " + inv.at(0).repr() + ", " + inv.at(1).repr() + ", and " + inv.at(2).repr() + ".";
        default: {
            std::string s = "Your inventory contains ";
            int i;
            for (i = 0; i < inv.size() - 1; i++) {
                s += inv.at(i).repr();
                s += ", ";
            }
            s += "and ";
            s += inv.at(i).repr();
            s += ".";
            return s;
        }
    }
}