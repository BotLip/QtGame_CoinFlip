#ifndef DATACONFIG_H
#define DATACONFIG_H

#include<QMap>
#include<QVector>

class DataConfig
{
public:
    DataConfig();
    QMap<int, QVector<QVector<int>>> myData;

};

#endif // DATACONFIG_H
