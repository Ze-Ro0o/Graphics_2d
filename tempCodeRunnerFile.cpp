
    case WM_COMMAND:
        switch (wParam)
        {
        case  (0):
            color = RGB(255, 0, 0);
            cout << "You are use Red color " << endl;
            break;
        case  (1):
            color = RGB(0, 110, 0);
            cout << "You are use Green color" << endl;
            break;
        case  (2):
            color = RGB(0, 0, 255);
            cout << "You are use Blue color" << endl;
            break;
        case  (3):
            color = RGB(255, 255, 0);
            cout << "You are use Yellow color" << endl;
            break;
        case  (4):
            color = RGB(0, 0, 0);
            cout << "You are use Black color" << endl;
            break;

        case  (5):
            color = RGB(255, 165, 0);
            cout << "You are use Orange color" << endl;
            break;

        case  (6):
            case_number = 6;
            cout << "You can Draw circle using Direct Algorithm...." << endl;
            break;
        case  (7):
            case_number = 7;
            cout << "You can Draw circle using Polar Algorithm...." << endl;
            break;

        case  (8):
            case_number = 8;
            cout << "You can Draw circle using Iterative Polar Algorithm...." << endl;

            break;
        case  (9):
            case_number = 9;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (10):
            case_number = 10;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (11):
            case_number = 11;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (12):
            case_number = 12;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (13):
            case_number = 13;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (14):
            case_number = 14;
            cout << "You can Draw circle using MidPoint Algorithm....." << endl;

            break;
        case  (15):
            case_number = 15;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (16):
            case_number = 16;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (17):
            case_number = 17;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;

        case  (18):
            case_number = 18;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (19):
            case_number = 19;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (20):
            case_number = 20;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (21):
            case_number = 21;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (22):
            case_number = 22;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (23):
            case_number = 23;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (24):
            case_number = 24;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (25):
            case_number = 25;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (26):
            case_number = 26;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (27):
            case_number = 27;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (28):
            case_number = 28;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (29):
            case_number = 29;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (30):
            case_number = 30;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (31):
            case_number = 31;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (32):
            case_number = 32;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (33):
            case_number = 33;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (34):
            case_number = 34;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (35):
            case_number = 35;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        case  (36):
            case_number = 36;
            cout << "You can Draw circle using MidPoint Modification Algorithm....." << endl;

            break;
        }
    case WM_LBUTTONDOWN:
    if (case_number >= 1 && case_number <= 3) //  (Direct, Polar, iterative Polar, midpoint and modified Midpoint)
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
        }