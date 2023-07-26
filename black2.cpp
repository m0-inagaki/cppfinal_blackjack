#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

class CardDeck {
    vector<pair<int, string>> deck;
    mt19937 rng;
    int sum_dealer;
    int sum_you;
    int dealer_win;
    int you_win;
    int draw;
   

public:
    CardDeck() {
        for (int i = 1; i <= 13; ++i) {
            for (int j = 0; j <= 3; ++j) {
                deck.push_back(make_pair(i, getSuit(j)));
            }
        }
        random_device rd;
        rng.seed(rd());
        int dealer_win = 0;
        int you_win = 0;
    }

    string getSuit(int suit) const {
        switch (suit) {
        case 0:
            return "Club";
        case 1:
            return "Diamonds";
        case 2:
            return "Hearts";
        case 3:
            return "Spades";
        default:
            return "";
        }
    }

    void shuffleDeck() {
        shuffle(deck.begin(), deck.end(), rng);
    }

    pair<int, string> drawCard() {
        if (!deck.empty()) {
            pair<int, string> card = deck.back();
            deck.pop_back();
            return card;
        }
        else {
            return make_pair(0, "");
            cout << "��������܂���" << endl;
        }
    }

    void dealer(const pair<int, string>& card) {
        if (card.first > 10) {
            sum_dealer += 10;
        }
        else {
            sum_dealer += card.first;
        }
        cout << "�f�B�[���[���������J�[�h:(" << card.first << ", " << card.second << ")" << "<���v:" << sum_dealer << ">" << endl;
    }

    void you(const pair<int, string>& card) {
        if (card.first > 10) {
            sum_you += 10;
        }
        else {
            sum_you += card.first;
        }
        cout << "���Ȃ����������J�[�h:(" << card.first << ", " << card.second << ")" << "<���v:" << sum_you << ">" << endl;
    }

    void judge(int& sum_dealer, int& sum_you) {
        cout<<"���Ȃ��̍��v:"<<sum_you<<"  "<<"�f�B�[���[�̍��v:"<<sum_dealer<<endl;
        if (21>=sum_dealer&&sum_dealer > sum_you) {
            cout << "���Ȃ��̕����ł��B" << endl;
            dealer_win += 1;
        }
        else if (sum_dealer>21&&21>sum_you) {
            cout << "���Ȃ��̏����ł�" << endl;
            you_win += 1;
        }
        else if (sum_dealer == sum_you) {
            cout << "���������ł��B" << endl;
            draw += 1;
        }
        else if (21>=sum_you&&sum_you > sum_dealer) {
            cout << "���Ȃ��̏����ł�" << endl;
            you_win += 1;  
        }
        else if (sum_you > 21&&21>sum_dealer) {
             cout << "���Ȃ��̕����ł��B" << endl;
             dealer_win += 1;
        }     
    }

    void judgeBorder(int& sum_dealer, int& sum_you) {
       if (sum_dealer > 21) {
           cout << "���Ȃ��̏����ł��ł��B" << endl;
           you_win += 1;
       }
        else if (sum_you > 21) {
            cout << "���Ȃ��̕����ł��B" << endl;
            dealer_win += 1;
        }
    }

    void reset() {
        sum_dealer = 0;
        sum_you = 0;
    }

    int getDealerWinCount() const {
        return dealer_win;
    }

    int getYouWinCount() const {
        return you_win;
    }

    int getdrawCount() const {
        return draw;
    }
};

int main() {
    CardDeck trump;
    char choice;
    int times = 1;
    
    do {
        trump.shuffleDeck();
        int sum_dealer = 0;
        int sum_you = 0;
        cout <<times << "��ڂ̃u���b�N�W���b�N���n�߂܂��B" << endl;
        pair<int, string> card = trump.drawCard();
        trump.dealer(card);
            if (card.first > 10) {
                sum_dealer += 10;
            }
            else {
                sum_dealer += card.first;
            }
        card = trump.drawCard();
        trump.you(card);
        if (card.first > 10) {
            sum_you += 10;
        }
        else {
            sum_you += card.first;
        }
        cout << "�J�[�h�������܂����H(y/n)" <<endl;

        while (true) {
            char word;
            cin >> word;
            if (word == 'y') {
                if (sum_you > 21) {
                    trump.judgeBorder(sum_dealer, sum_you);
                    break;
                }
                card = trump.drawCard();
                trump.you(card);
                    if (card.first >= 10) {
                        sum_you += 10;
                    }
                    else {
                        sum_you += card.first;
                    }   
                if (sum_you > 21) {
                    trump.judgeBorder(sum_dealer, sum_you);
                    break;
                }
                cout << "�J�[�h�������܂����H(y/n)" ;
                cout << endl;
            }

            if (word == 'n') {
                while (sum_dealer < 17) {
                    if (sum_dealer > sum_you) {
                        trump.judge(sum_dealer, sum_you);
                        break; 
                    }
                    card = trump.drawCard();
                    trump.dealer(card);
                        if (card.first > 10) {
                            sum_dealer += 10;
                        }
                        else {
                            sum_dealer += card.first;
                        }
                    if (sum_dealer>=17&&sum_dealer <= 21) {
                        trump.judge(sum_dealer, sum_you);
                        break;
                    }
                }
                if(sum_dealer > 21) {
                    trump.judgeBorder(sum_dealer, sum_you);   
                }
                break;
            }
        }
        times += 1;
        cout << "������x�v���C���܂����H (y/n) " <<"<����" << 10- times << "��ΐ�ł��܂��B> " << endl;
        cin >> choice;
        trump.reset();
        cout << endl;
        if (times == 10 || choice != 'y') {
            cout << "����Ńu���b�N�W���b�N�͏I���܂��B" << endl;
            cout << "�f�B�[���[�̏�����:" << trump.getDealerWinCount()<<"  ";
            cout << "����������:" << trump.getdrawCount() << "  ";
            cout << "���Ȃ��̏�����:" << trump.getYouWinCount() << endl;
            if (trump.getDealerWinCount() > trump.getYouWinCount()) {
                cout << "�f�B�[���[�̏����ł��B" << endl;
            }
            else if (trump.getDealerWinCount() < trump.getYouWinCount()) {
                cout << "���Ȃ��̏����ł��B" << endl;
            }
            else{
                cout << "���������ł��B" << endl;
            }
        }
    } while (choice == 'y'&&times<=9);
}
