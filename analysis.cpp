#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
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

    bool operator<(const Cube &c) const
    {
        if (EO<c.EO)
            return true;
        if (EO>c.EO)
            return false;
        if (EP<c.EP)
            return true;
        if (EP>c.EP)
            return false;
        if (CO<c.CO)
            return true;
        if (CO>c.CO)
            return false;
        if (CP<c.CP)
            return true;
        if (CP>c.CP)
            return false;
        return false;
    }

    // E列を無視したEPとCPの情報を圧縮。
    uint64_t compress() const
    {
        uint64_t c = 0;
        for (int i=0; i<4; i++)
            c |= uint64_t(EP[i]<4?EP[i]:EP[i]-4)<<(i*3);
        for (int i=8; i<12; i++)
            c |= uint64_t(EP[i]<4?EP[i]:EP[i]-4)<<(i*3-12);
        for (int i=0; i<8; i++)
            c |= uint64_t(CP[i])<<(i*3+24);
        return c;
    }

    // compress で圧縮した情報を復元。
    void decompress(uint64_t c)
    {
        for (int i=0; i<4; i++)
        {
            uint8_t t = c>>(i*3)&0b111;
            EP[i] = t<4?t:t+4;
        }
        for (int i=8; i<12; i++)
        {
            uint8_t t = c>>(i*3-12)&0b111;
            EP[i] = t<4?t:t+4;
        }
        for (int i=0; i<8; i++)
            CP[i] = c>>(i*3+24)&0b111;
    }
};

int main()
{
    // start -> EO
    {
        printf("start -> EO\n");

        Cube cube;
        // EPとCPは区別しない。
        cube.EP = vector<uint8_t>(12);
        cube.CP = vector<uint8_t>(8);

        vector<int> moves = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

        vector<set<Cube>> cubes(1);
        cubes[0].insert(cube);

        for (int d=0; !cubes[d].empty(); d++)
        {
            printf("%3d %8lld\n", d, cubes[d].size());

            cubes.push_back(set<Cube>());

            for (Cube cube: cubes[d])
                for (int m: moves)
                {
                    cube.move(m);
                    // COは区別しない。
                    cube.CO = vector<uint8_t>(8);

                    bool found = false;
                    for (int dd=0; dd<=d+1 && !found; dd++)
                        if (cubes[dd].count(cube)>0)
                            found = true;
                    if (!found)
                        cubes[d+1].insert(cube);

                    cube.move(m/3*3+2-m%3);
                }
        }
    }

    // EO -> DR
    {
        printf("EO -> DR\n");

        Cube cube;
        // EPはE列かどうかだけを区別する。
        cube.EP = vector<uint8_t>{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
        // CPは区別しない。
        cube.CP = vector<uint8_t>(8);

        vector<int> moves = {0, 1, 2, 3, 4, 5, 7, 9, 10, 11, 12, 13, 14, 16};

        vector<set<Cube>> cubes(1);
        cubes[0].insert(cube);

        for (int d=0; !cubes[d].empty(); d++)
        {
            printf("%3d %8lld\n", d, cubes[d].size());

            cubes.push_back(set<Cube>());

            for (Cube cube: cubes[d])
                for (int m: moves)
                {
                    cube.move(m);

                    bool found = false;
                    for (int dd=0; dd<=d+1 && !found; dd++)
                        if (cubes[dd].count(cube)>0)
                            found = true;
                    if (!found)
                        cubes[d+1].insert(cube);

                    cube.move(m/3*3+2-m%3);
                }
        }
    }

    // HTR -> finish
    set<Cube> hdr_cubes;
    {
        printf("HTR -> finish\n");

        Cube cube;
        vector<int> moves = {1, 4, 7, 10, 13, 16};

        vector<set<Cube>> cubes(1);
        cubes[0].insert(cube);

        for (int d=0; !cubes[d].empty(); d++)
        {
            printf("%3d %8lld\n", d, cubes[d].size());

            cubes.push_back(set<Cube>());

            for (Cube cube: cubes[d])
                for (int m: moves)
                {
                    cube.move(m);

                    bool found = false;
                    for (int dd=0; dd<=d+1 && !found; dd++)
                        if (cubes[dd].count(cube)>0)
                            found = true;
                    if (!found)
                        cubes[d+1].insert(cube);

                    cube.move(m/3*3+2-m%3);
                }
        }

        for (set<Cube> &C: cubes)
            hdr_cubes.insert(C.begin(), C.end());
    }

    // DR -> HTR
    {
        printf("DR -> HTR\n");

        vector<int> moves = {0, 1, 2, 4, 7, 9, 10, 11, 13, 16};

        vector<unordered_set<uint64_t>> cubes(1);
        for (Cube cube: hdr_cubes)
            // DRの動きでE列のEPは変化しないので、無視して扱う。
            cubes[0].insert(cube.compress());

        for (int d=0; !cubes[d].empty(); d++)
        {
            if (cubes[d].size()%cubes[0].size()!=0)
                printf("error\n");
            printf("%3d %8lld\n", d, cubes[d].size()/cubes[0].size());

            cubes.push_back(unordered_set<uint64_t>());

            Cube cube;
            for (uint64_t c: cubes[d])
            {
                cube.decompress(c);

                for (int m: moves)
                {
                    cube.move(m);

                    uint64_t c2 = cube.compress();
                    bool found = false;
                    for (int dd=0; dd<=d+1 && !found; dd++)
                        if (cubes[dd].count(c2)>0)
                            found = true;
                    if (!found)
                        cubes[d+1].insert(c2);

                    cube.move(m/3*3+2-m%3);
                }
            }
        }
    }
}
