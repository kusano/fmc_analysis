#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <functional>
using namespace std;

// x1 <- x2 <- x3 <- x4 <- x1
void rotate(uint8_t &x1, uint8_t &x2, uint8_t &x3, uint8_t &x4)
{
    uint8_t t = x1;
    x1 = x2;
    x2 = x3;
    x3 = x4;
    x4 = t;
}

struct Cube
{
    vector<uint8_t> EO, EP, CO, CP;

    Cube()
    {
        EO = vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        EP = vector<uint8_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        CO = vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0};
        CP = vector<uint8_t>{0, 1, 2, 3, 4, 5, 6, 7};
    }

    void move(int m)
    {
        switch (m)
        {
        case 0: // U
            rotate(EO[0], EO[3], EO[2], EO[1]);
            rotate(EP[0], EP[3], EP[2], EP[1]);
            rotate(CO[0], CO[3], CO[2], CO[1]);
            rotate(CP[0], CP[3], CP[2], CP[1]);
            break;
        case 1: // U2
            swap(EO[0], EO[2]), swap(EO[3], EO[1]);
            swap(EP[0], EP[2]), swap(EP[3], EP[1]);
            swap(CO[0], CO[2]), swap(CO[3], CO[1]);
            swap(CP[0], CP[2]), swap(CP[3], CP[1]);
            break;
        case 2: // U'
            rotate(EO[0], EO[1], EO[2], EO[3]);
            rotate(EP[0], EP[1], EP[2], EP[3]);
            rotate(CO[0], CO[1], CO[2], CO[3]);
            rotate(CP[0], CP[1], CP[2], CP[3]);
            break;
        case 3: // R
            rotate(EO[1], EO[6], EO[9], EO[5]);
            rotate(EP[1], EP[6], EP[9], EP[5]);
            rotate(CO[1], CO[2], CO[6], CO[5]);
            rotate(CP[1], CP[2], CP[6], CP[5]);
            (CO[1] += 1) %= 3;
            (CO[2] += 2) %= 3;
            (CO[6] += 1) %= 3;
            (CO[5] += 2) %= 3;
            break;
        case 4: // R2
            swap(EO[1], EO[9]), swap(EO[6], EO[5]);
            swap(EP[1], EP[9]), swap(EP[6], EP[5]);
            swap(CO[1], CO[6]), swap(CO[5], CO[2]);
            swap(CP[1], CP[6]), swap(CP[5], CP[2]);
            break;
        case 5: // R'
            rotate(EO[1], EO[5], EO[9], EO[6]);
            rotate(EP[1], EP[5], EP[9], EP[6]);
            rotate(CO[1], CO[5], CO[6], CO[2]);
            rotate(CP[1], CP[5], CP[6], CP[2]);
            (CO[1] += 1) %= 3;
            (CO[5] += 2) %= 3;
            (CO[6] += 1) %= 3;
            (CO[2] += 2) %= 3;
            break;
        case 6: // F
            rotate(EO[2], EO[7], EO[10], EO[6]);
            rotate(EP[2], EP[7], EP[10], EP[6]);
            rotate(CO[3], CO[7], CO[6], CO[2]);
            rotate(CP[3], CP[7], CP[6], CP[2]);
            EO[2] ^= 1;
            EO[7] ^= 1;
            EO[10] ^= 1;
            EO[6] ^= 1;
            (CO[3] += 2) %= 3;
            (CO[7] += 1) %= 3;
            (CO[6] += 2) %= 3;
            (CO[2] += 1) %= 3;
            break;
        case 7: // F2
            swap(EO[2], EO[10]), swap(EO[7], EO[6]);
            swap(EP[2], EP[10]), swap(EP[7], EP[6]);
            swap(CO[3], CO[6]), swap(CO[7], CO[2]);
            swap(CP[3], CP[6]), swap(CP[7], CP[2]);
            break;
        case 8: // F'
            rotate(EO[2], EO[6], EO[10], EO[7]);
            rotate(EP[2], EP[6], EP[10], EP[7]);
            rotate(CO[3], CO[2], CO[6], CO[7]);
            rotate(CP[3], CP[2], CP[6], CP[7]);
            EO[2] ^= 1;
            EO[6] ^= 1;
            EO[10] ^= 1;
            EO[7] ^= 1;
            (CO[3] += 2) %= 3;
            (CO[2] += 1) %= 3;
            (CO[6] += 2) %= 3;
            (CO[7] += 1) %= 3;
            break;
        case 9: // D
            rotate(EO[8], EO[9], EO[10], EO[11]);
            rotate(EP[8], EP[9], EP[10], EP[11]);
            rotate(CO[4], CO[5], CO[6], CO[7]);
            rotate(CP[4], CP[5], CP[6], CP[7]);
            break;
        case 10: // D2
            swap(EO[8], EO[10]), swap(EO[9], EO[11]);
            swap(EP[8], EP[10]), swap(EP[9], EP[11]);
            swap(CO[4], CO[6]), swap(CO[5], CO[7]);
            swap(CP[4], CP[6]), swap(CP[5], CP[7]);
            break;
        case 11: // D'
            rotate(EO[8], EO[11], EO[10], EO[9]);
            rotate(EP[8], EP[11], EP[10], EP[9]);
            rotate(CO[4], CO[7], CO[6], CO[5]);
            rotate(CP[4], CP[7], CP[6], CP[5]);
            break;
        case 12: // L
            rotate(EO[3], EO[4], EO[11], EO[7]);
            rotate(EP[3], EP[4], EP[11], EP[7]);
            rotate(CO[0], CO[4], CO[7], CO[3]);
            rotate(CP[0], CP[4], CP[7], CP[3]);
            (CO[0] += 2) %= 3;
            (CO[4] += 1) %= 3;
            (CO[7] += 2) %= 3;
            (CO[3] += 1) %= 3;
            break;
        case 13: // L2
            swap(EO[3], EO[11]), swap(EO[4], EO[7]);
            swap(EP[3], EP[11]), swap(EP[4], EP[7]);
            swap(CO[0], CO[7]), swap(CO[4], CO[3]);
            swap(CP[0], CP[7]), swap(CP[4], CP[3]);
            break;
        case 14: // L'
            rotate(EO[3], EO[7], EO[11], EO[4]);
            rotate(EP[3], EP[7], EP[11], EP[4]);
            rotate(CO[0], CO[3], CO[7], CO[4]);
            rotate(CP[0], CP[3], CP[7], CP[4]);
            (CO[0] += 2) %= 3;
            (CO[3] += 1) %= 3;
            (CO[7] += 2) %= 3;
            (CO[4] += 1) %= 3;
            break;
        case 15: // B
            rotate(EO[0], EO[5], EO[8], EO[4]);
            rotate(EP[0], EP[5], EP[8], EP[4]);
            rotate(CO[0], CO[1], CO[5], CO[4]);
            rotate(CP[0], CP[1], CP[5], CP[4]);
            EO[0] ^= 1;
            EO[5] ^= 1;
            EO[8] ^= 1;
            EO[4] ^= 1;
            (CO[0] += 1) %= 3;
            (CO[1] += 2) %= 3;
            (CO[5] += 1) %= 3;
            (CO[4] += 2) %= 3;
            break;
        case 16: // B2
            swap(EO[0], EO[8]), swap(EO[5], EO[4]);
            swap(EP[0], EP[8]), swap(EP[5], EP[4]);
            swap(CO[0], CO[5]), swap(CO[1], CO[4]);
            swap(CP[0], CP[5]), swap(CP[1], CP[4]);
            break;
        case 17: // B'
            rotate(EO[0], EO[4], EO[8], EO[5]);
            rotate(EP[0], EP[4], EP[8], EP[5]);
            rotate(CO[0], CO[4], CO[5], CO[1]);
            rotate(CP[0], CP[4], CP[5], CP[1]);
            EO[0] ^= 1;
            EO[4] ^= 1;
            EO[8] ^= 1;
            EO[5] ^= 1;
            (CO[0] += 1) %= 3;
            (CO[4] += 2) %= 3;
            (CO[5] += 1) %= 3;
            (CO[1] += 2) %= 3;
            break;
        }
    }

    string str() const
    {
        vector<string> E = {"UB", "UR", "UF", "UL", "BL", "BR", "FR", "FL", "DB", "DR", "DF", "DL"};
        vector<string> C = {"ULB", "UBR", "URF", "UFL", "DBL", "DRB", "DFR", "DLF"};

        auto e = [&](int p, int o) -> char
        {
            return E[EP[p]][(2-EO[p]+o)%2];
        };
        auto c = [&](int p, int o) -> char
        {
            return C[CP[p]][(3-CO[p]+o)%3];
        };

        string res = string() +
            ' '      + ' '      + ' '      + c( 0, 0) + e( 0, 0) + c( 1, 0) + '\n' +
            ' '      + ' '      + ' '      + e( 3, 0) + 'U'      + e( 1, 0) + '\n' +
            ' '      + ' '      + ' '      + c( 3, 0) + e( 2, 0) + c( 2, 0) + '\n' +
            c( 0, 1) + e( 3, 1) + c( 3, 2) + c( 3, 1) + e( 2, 1) + c( 2, 2) + c( 2, 1) + e( 1, 1) + c( 1, 2) + c( 1, 1) + e( 0, 1) + c( 0, 2) + '\n' +
            e( 4, 1) + 'L'      + e( 7, 1) + e( 7, 0) + 'F'      + e( 6, 0) + e( 6, 1) + 'R'      + e( 5, 1) + e( 5, 0) + 'B'      + e( 4, 0) + '\n' +
            c( 4, 2) + e(11, 1) + c( 7, 1) + c( 7, 2) + e(10, 1) + c( 6, 1) + c( 6, 2) + e( 9, 1) + c( 5, 1) + c( 5, 2) + e( 8, 1) + c( 4, 1) + '\n' +
            ' '      + ' '      + ' '      + c( 7, 0) + e(10, 0) + c( 6, 0) + '\n' +
            ' '      + ' '      + ' '      + e(11, 0) + 'D'      + e( 9, 0) + '\n' +
            ' '      + ' '      + ' '      + c( 4, 0) + e( 8, 0) + c( 5, 0) + '\n';

        string colored;
        for (char c: res)
            switch (c)
            {
            case 'U': colored += "\x1b[47mU \x1b[0m"; break;
            case 'D': colored += "\x1b[43mD \x1b[0m"; break;
            case 'L': colored += "\x1b[45mL \x1b[0m"; break;
            case 'R': colored += "\x1b[41mR \x1b[0m"; break;
            case 'F': colored += "\x1b[42mF \x1b[0m"; break;
            case 'B': colored += "\x1b[44mB \x1b[0m"; break;
            case ' ': colored += "  "; break;
            case '\n': colored += "\n"; break;
            default:
                colored += "ERROR";
            }

        return colored;
    }
};

int main()
{
    vector<string> move_names = {
        "U", "U2", "U'",
        "R", "R2", "R'",
        "F", "F2", "F'",
        "D", "D2", "D'",
        "L", "L2", "L'",
        "B", "B2", "B'",
    };

    cout<<"Scramble: ";
    string line;
    getline(cin, line);
    stringstream ss(line);

    Cube cube;
    string move;
    while (ss>>move)
    {
        bool ok = false;
        for (int m=0; m<18; m++)
            if (move_names[m]==move)
            {
                cube.move(m);
                ok = true;
            }
        if (!ok)
        {
            cerr<<"Invalid move: "<<move<<endl;
            return 1;
        }
    }

    cout<<cube.str()<<endl;

    vector<int> allowed;
    vector<int> moves;

    function<bool(int, int)> search = [&](int stage, int depth)
    {
        if (stage==0)
        {
            bool ok = true;
            for (int i=0; i<12 && ok; i++)
                if (cube.EO[i]!=0)
                    ok = false;
            if (ok)
                return true;
        }
        if (stage==1)
        {
            bool ok = true;
            for (int i=4; i<8 && ok; i++)
                if (cube.EP[i]/4!=1)
                    ok = false;
            for (int i=0; i<8 && ok; i++)
                if (cube.CO[i]!=0)
                    ok = false;
            if (ok)
                return true;
        }
        if (stage==2)
        {
            if ((cube.EP[ 0]==0 || cube.EP[ 0]==2 || cube.EP[ 0]==8 || cube.EP[ 0]==10) &&
                (cube.EP[ 2]==0 || cube.EP[ 2]==2 || cube.EP[ 2]==8 || cube.EP[ 2]==10) &&
                (cube.EP[ 8]==0 || cube.EP[ 8]==2 || cube.EP[ 8]==8 || cube.EP[ 8]==10) &&
                (cube.EP[10]==0 || cube.EP[10]==2 || cube.EP[10]==8 || cube.EP[10]==10) &&
                (cube.CP[ 0]==0 || cube.CP[ 0]==2 || cube.CP[ 0]==5 || cube.CP[ 0]== 7) &&
                (cube.CP[ 2]==0 || cube.CP[ 2]==2 || cube.CP[ 2]==5 || cube.CP[ 2]== 7) &&
                (cube.CP[ 5]==0 || cube.CP[ 5]==2 || cube.CP[ 5]==5 || cube.CP[ 5]== 7) &&
                (cube.CP[ 7]==0 || cube.CP[ 7]==2 || cube.CP[ 7]==5 || cube.CP[ 7]== 7))
            {
                if ((cube.CP[ 0]/4==0)==(cube.CP[ 4]/4==0) &&
                    (cube.CP[ 1]/4==0)==(cube.CP[ 5]/4==0) &&
                    (cube.CP[ 2]/4==0)==(cube.CP[ 6]/4==0) &&
                    (cube.CP[ 3]/4==0)==(cube.CP[ 7]/4==0) ||
                    (cube.CP[ 0]/4==0)!=(cube.CP[ 4]/4==0) &&
                    (cube.CP[ 1]/4==0)!=(cube.CP[ 5]/4==0) &&
                    (cube.CP[ 2]/4==0)!=(cube.CP[ 6]/4==0) &&
                    (cube.CP[ 3]/4==0)!=(cube.CP[ 7]/4==0))
                {
                    vector<bool> U(8);
                    int p = 0;
                    for (int i=0; i<8; i++)
                        if (!U[i])
                        {
                            int c = 0;
                            int t = i;
                            while (!U[t])
                            {
                                U[t] = true;
                                c++;
                                t = cube.CP[t];
                            }
                            if (c%2==0)
                                p ^= 1;
                        }
                    if (p==0)
                        return true;
                }
            }
        }
        if (stage==3)
        {
            bool ok = true;
            for (int i=0; i<12 && ok; i++)
                if (cube.EP[i]!=i)
                    ok = false;
            for (int i=0; i<8 && ok; i++)
                if (cube.CP[i]!=i)
                    ok = false;
            if (ok)
                return true;
        }

        if (depth==0)
            return false;

        for (int m: allowed)
        {
            if (moves.size()>0)
            {
                int pm = moves.back();
                if (pm/3==m/3 ||
                    pm/3==3 && m/3==0 ||
                    pm/3==4 && m/3==1 ||
                    pm/3==5 && m/3==2)
                    continue;
            }

            cube.move(m);
            moves.push_back(m);

            if (search(stage, depth-1))
                return true;

            cube.move(m/3*3+(2-m%3));
            moves.pop_back();
        }

        return false;
    };

    int steps = 0;

    // EO
    allowed = vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    for (int depth=0; ; depth++)
        if (search(0, depth))
            break;

    steps += (int)moves.size();
    for (int m: moves)
        cout<<" "<<move_names[m];
    cout<<" // EO (F/B) ("<<moves.size()<<"/"<<steps<<")"<<endl;

    // DR
    allowed = vector<int>{0, 1, 2, 3, 4, 5, 7, 9, 10, 11, 12, 13, 14, 16};
    moves.clear();
    for (int depth=0; ; depth++)
        if (search(1, depth))
            break;

    steps += (int)moves.size();
    for (int m: moves)
        cout<<" "<<move_names[m];
    cout<<" // DR (U/D) ("<<moves.size()<<"/"<<steps<<")"<<endl;

    // HTR
    allowed = vector<int>{0, 1, 2, 4, 7, 9, 10, 11, 13, 16};
    moves.clear();
    for (int depth=0; ; depth++)
        if (search(2, depth))
            break;

    steps += (int)moves.size();
    for (int m: moves)
        cout<<" "<<move_names[m];
    cout<<" // HTR ("<<moves.size()<<"/"<<steps<<")"<<endl;

    // finish
    allowed = vector<int>{1, 4, 7, 10, 13, 16};
    moves.clear();
    for (int depth=0; ; depth++)
        if (search(3, depth))
            break;

    steps += (int)moves.size();
    for (int m: moves)
        cout<<" "<<move_names[m];
    cout<<" // finish ("<<moves.size()<<"/"<<steps<<")"<<endl;
}
