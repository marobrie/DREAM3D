/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "DREAM3DLib/DataContainers/EdgeDataContainer.h"

// C Includes

// C++ Includes
#include <iostream>
#include <fstream>


// DREAM3D Includes
#include "DREAM3DLib/Math/DREAM3DMath.h"


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
EdgeDataContainer::EdgeDataContainer() :
VertexDataContainer(),
m_NumEdgeTuples(0)
{
  setName(DREAM3D::HDF5::EdgeDataContainerName);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
EdgeDataContainer::~EdgeDataContainer()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DOES_DATASET_EXIST_DEFN(EdgeDataContainer, EdgeData)
DOES_DATASET_EXIST_DEFN(EdgeDataContainer, EdgeFieldData)
DOES_DATASET_EXIST_DEFN(EdgeDataContainer, EdgeEnsembleData)

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer EdgeDataContainer::getEdgeData(const QString &name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_EdgeData.find(name);
  if ( it == m_EdgeData.end() )
  {
    return IDataArray::NullPointer();
  }
  return it.value();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::addEdgeData(const QString &name, IDataArray::Pointer data)
{
  if (data->GetName().compare(name) != 0)
  {
    qDebug() << "Adding Edge array with different array name than key name" << "\n";
    qDebug() << "Key name: " << name << "\n";
    qDebug() << "Array Name:" << data->GetName() << "\n";
    data->SetName(name);
  }
  m_EdgeData[name] = data;
  m_NumEdgeTuples = data->getNumberOfTuples();
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer EdgeDataContainer::removeEdgeData(const QString &name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_EdgeData.find(name);
  if ( it == m_EdgeData.end() )
  {
    return IDataArray::NullPointer();
  }
  IDataArray::Pointer p = it.value();
  m_EdgeData.erase(it);
  return p;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::clearEdgeData()
{
  m_EdgeData.clear();
  m_NumEdgeTuples = 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QList<QString> EdgeDataContainer::getEdgeArrayNameList()
{
  QList<QString> keys;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_EdgeData.begin(); iter != m_EdgeData.end(); ++iter)
  {
    keys.push_back( iter.key());
  }
  return keys;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int EdgeDataContainer::getNumEdgeArrays()
{
  return static_cast<int>(m_EdgeData.size());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer EdgeDataContainer::getEdgeFieldData(const QString &name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_EdgeFieldData.find(name);
  if ( it == m_EdgeFieldData.end() )
  {
    return IDataArray::NullPointer();
  }
  return it.value();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::addEdgeFieldData(const QString &name, IDataArray::Pointer data)
{
  if (data->GetName().compare(name) != 0)
  {
    qDebug() << "Adding Field array with different array name than key name" << "\n";
    qDebug() << "Key name: " << name << "\n";
    qDebug() << "Array Name:" << data->GetName() << "\n";
    data->SetName(name);
  }
  m_EdgeFieldData[name] = data;
  m_NumEdgeFieldTuples = data->getNumberOfTuples();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer EdgeDataContainer::removeEdgeFieldData(const QString &name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_EdgeFieldData.find(name);
  if ( it == m_EdgeFieldData.end() )
  {
    return IDataArray::NullPointer();
  }
  IDataArray::Pointer p = it.value();
  m_EdgeFieldData.erase(it);
  return p;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::clearEdgeFieldData()
{
  m_EdgeFieldData.clear();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QList<QString> EdgeDataContainer::getEdgeFieldArrayNameList()
{
  QList<QString> keys;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_EdgeFieldData.begin(); iter != m_EdgeFieldData.end(); ++iter)
  {
    keys.push_back( iter.key());
  }
  return keys;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int EdgeDataContainer::getNumEdgeFieldArrays()
{
  return static_cast<int>(m_EdgeFieldData.size());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::resizeEdgeFieldDataArrays(size_t size)
{
 // int success = 0;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_EdgeFieldData.begin(); iter != m_EdgeFieldData.end(); ++iter)
  {
    //qDebug() << "Resizing Array '" << iter.key() << "' : " << success << "\n";
    IDataArray::Pointer d = iter.value();
    d->Resize(size);
  }
  m_NumEdgeFieldTuples = size;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer EdgeDataContainer::getEdgeEnsembleData(const QString &name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_EdgeEnsembleData.find(name);
  if ( it == m_EdgeEnsembleData.end() )
  {
    return IDataArray::NullPointer();
  }
  return it.value();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::addEdgeEnsembleData(const QString &name, IDataArray::Pointer data)
{
  if (data->GetName().compare(name) != 0)
  {
    qDebug() << "Adding Ensemble array with different array name than key name" << "\n";
    qDebug() << "Key name: " << name << "\n";
    qDebug() << "Array Name:" << data->GetName() << "\n";
    data->SetName(name);
  }
  m_EdgeEnsembleData[name] = data;
  m_NumEdgeEnsembleTuples = data->getNumberOfTuples();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IDataArray::Pointer EdgeDataContainer::removeEdgeEnsembleData(const QString &name)
{
  QMap<QString, IDataArray::Pointer>::iterator it;
  it =  m_EdgeEnsembleData.find(name);
  if ( it == m_EdgeEnsembleData.end() )
  {
    return IDataArray::NullPointer();
  }
  IDataArray::Pointer p = it.value();
  m_EdgeEnsembleData.erase(it);
  return p;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::clearEdgeEnsembleData()
{
  m_EdgeEnsembleData.clear();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QList<QString> EdgeDataContainer::getEdgeEnsembleArrayNameList()
{
  QList<QString> keys;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_EdgeEnsembleData.begin(); iter != m_EdgeEnsembleData.end(); ++iter)
  {
    keys.push_back( iter.key());
  }
  return keys;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int EdgeDataContainer::getNumEdgeEnsembleArrays()
{
  return static_cast<int>(m_EdgeEnsembleData.size());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EdgeDataContainer::resizeEdgeEnsembleDataArrays(size_t size)
{
 // int success = 0;
  for(QMap<QString, IDataArray::Pointer>::iterator iter = m_EdgeEnsembleData.begin(); iter != m_EdgeEnsembleData.end(); ++iter)
  {
    //qDebug() << "Resizing Array '" << iter.key() << "' : " << success << "\n";
    IDataArray::Pointer d = iter.value();
    d->Resize(size);
  }
  m_NumEdgeEnsembleTuples = size;
}
