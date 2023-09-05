#include "dataconfig.h"

DataConfig::DataConfig()
{
    int arr1[4][4] = {{1,1,1,1},
                     {1,1,0,1},
                     {1,0,0,0},
                     {1,1,0,1}
                    };
    QVector<QVector<int>> v(4, QVector<int>(4));
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            v[i][j] = arr1[i][j];
        }
    }
    this->myData[1] = v;


    int arr2[4][4] =  {{0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0}
                      };
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            v[i][j] = arr2[i][j];
        }
    }
    this->myData[2] = v;



}
