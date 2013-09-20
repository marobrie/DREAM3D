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

#include "ArraySelectionWidget.h"



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ArraySelectionWidget::ArraySelectionWidget(QWidget *parent) :
  QTabWidget(parent)
{
  setupUi(this);
  setupGui();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ArraySelectionWidget::~ArraySelectionWidget()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::setupGui()
{
  connect(volumeVertexArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(volumeEdgeArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(volumeFaceArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(volumeCellArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(volumeCellFieldArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(volumeCellEnsembleArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));

  connect(surfaceVertexArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(surfaceFaceArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(surfaceEdgeArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(surfaceFaceFieldArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(surfaceFaceEnsembleArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));

  connect(edgeVertexArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(edgeEdgeArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(edgeEdgeFieldArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(edgeEdgeEnsembleArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));

  connect(vertexVertexArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(vertexVertexFieldArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));
  connect(vertexVertexEnsembleArrayList, SIGNAL(	itemChanged ( QListWidgetItem*)),
          this, SLOT(arrayListUpdated(QListWidgetItem*)));

}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::arrayListUpdated(QListWidgetItem *item)
{
  emit arrayListsChanged();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::populateArrayNames(DataContainerArray::Pointer dca)
{
  BOOST_ASSERT(false);
#if 0
  populateVolumeArrayNames(vldc);
  populateSurfaceArrayNames(sdc);
  populateEdgeArrayNames(edc);
  populateVertexArrayNames(vdc);
#endif
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::populateVolumeArrayNames(VolumeDataContainer::Pointer vldc)
{
  QList<QString> vertexNames = vldc->getVertexArrayNameList();
  populateArrayList(volumeVertexArrayList, vertexNames, volumeVertexCB);

  QList<QString> edgeNames = vldc->getEdgeArrayNameList();
  populateArrayList(volumeEdgeArrayList, edgeNames, volumeEdgeCB);

  QList<QString> faceNames = vldc->getFaceArrayNameList();
  populateArrayList(volumeFaceArrayList, faceNames, volumeFaceCB);

  QList<QString> cellNames = vldc->getCellArrayNameList();
  populateArrayList(volumeCellArrayList, cellNames, volumeCellCB);

  QList<QString> fieldNames = vldc->getCellFieldArrayNameList();
  populateArrayList(volumeCellFieldArrayList, fieldNames, volumeCellFieldCB);

  QList<QString> ensembleNames = vldc->getCellEnsembleArrayNameList();
  populateArrayList(volumeCellEnsembleArrayList, ensembleNames, volumeCellEnsembleCB);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::populateSurfaceArrayNames(SurfaceDataContainer::Pointer sdc)
{
  QList<QString> vertexNames = sdc->getVertexArrayNameList();
  populateArrayList(surfaceVertexArrayList, vertexNames, surfaceVertexArraysCB);

  QList<QString> edgeNames = sdc->getEdgeArrayNameList();
  populateArrayList(surfaceEdgeArrayList, edgeNames, surfaceEdgeArraysCB);

  QList<QString> faceNames = sdc->getFaceArrayNameList();
  populateArrayList(surfaceFaceArrayList, faceNames, surfaceFaceArraysCB);

  QList<QString> fieldNames = sdc->getFaceFieldArrayNameList();
  populateArrayList(surfaceFaceFieldArrayList, fieldNames, surfaceFaceFieldArraysCB);

  QList<QString> ensembleNames = sdc->getFaceEnsembleArrayNameList();
  populateArrayList(surfaceFaceEnsembleArrayList, ensembleNames, surfaceFaceEnsembleArraysCB);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::populateEdgeArrayNames(EdgeDataContainer::Pointer edc)
{
  QList<QString> vertexNames = edc->getVertexArrayNameList();
  populateArrayList(edgeVertexArrayList, vertexNames, edgeVertexCB);

  QList<QString> edgeNames = edc->getEdgeArrayNameList();
  populateArrayList(edgeEdgeArrayList, edgeNames, edgeEdgeCB);

  QList<QString> fieldNames = edc->getEdgeFieldArrayNameList();
  populateArrayList(edgeEdgeFieldArrayList, fieldNames, edgeEdgeFieldCB);

  QList<QString> ensembleNames = edc->getEdgeEnsembleArrayNameList();
  populateArrayList(edgeEdgeEnsembleArrayList, ensembleNames, edgeEdgeEnsembleCB);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::populateVertexArrayNames(VertexDataContainer::Pointer vdc)
{
  QList<QString> vertexNames = vdc->getVertexArrayNameList();
  populateArrayList(vertexVertexArrayList, vertexNames, NULL);

  QList<QString> fieldNames = vdc->getVertexFieldArrayNameList();
  populateArrayList(vertexVertexFieldArrayList, fieldNames, NULL);

  QList<QString> ensembleNames = vdc->getVertexEnsembleArrayNameList();
  populateArrayList(vertexVertexEnsembleArrayList, ensembleNames, NULL);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::populateArrayList(QListWidget* listWidget, QList<QString> &arrayNames, QCheckBox* cb)
{
  // Convert from STL container to Qt Container then pass through to the next method.
  QStringList qArrayNames;
  for(QList<QString>::iterator iter = arrayNames.begin(); iter != arrayNames.end(); ++iter)
  {
    qArrayNames << (*iter);
  }
  populateArrayList(listWidget, qArrayNames, cb);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::populateArrayList(QListWidget* listWidget, QStringList &arrayNames, QCheckBox* cb)
{
  QStringList selectedArrays;
  int listWidgetCount = listWidget->count();
  // First loop through and get the list of arrays that were selected
  for(qint32 i = 0; i < listWidgetCount; ++i)
  {
    if (listWidget->item(i)->checkState() == Qt::Checked)
    {
      selectedArrays << listWidget->item(i)->text();
    }
  }

  // Now clear the list and start dropping in the array names checking for any previous selections
  int selectedCount = 0;
  listWidget->blockSignals(true);
  listWidget->clear();
  foreach(QString name, arrayNames)
  {
    listWidget->addItem(name);
    Qt::CheckState checked = Qt::Unchecked;
    if (selectedArrays.contains(name) == true) {
      checked = Qt::Checked;
      selectedCount++;
    }
    listWidget->item(listWidget->count() - 1)->setCheckState(checked);
  }

// Now make sure to check the "Select All" checkbox for this type of data
  listWidgetCount = listWidget->count();
  if (cb != NULL && listWidgetCount > 0)
  {
    cb->blockSignals(true);
    cb->setChecked(listWidgetCount == selectedCount);
    cb->blockSignals(false);
  }


//  qDebug() << "List Widget: " << listWidget->objectName() << " Count: " << listWidget->count() << "\n";
  listWidget->blockSignals(false);

}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_vertexVertexCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    vertexVertexCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(vertexVertexArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_vertexVertexFieldCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    vertexVertexFieldCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(vertexVertexFieldArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_vertexVertexEnsembleCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    vertexVertexEnsembleCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(vertexVertexEnsembleArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_edgeVertexCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    edgeVertexCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(edgeVertexArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_edgeEdgeCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    edgeEdgeCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(edgeEdgeArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_edgeEdgeFieldCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    edgeEdgeFieldCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(edgeEdgeFieldArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_edgeEdgeEnsembleCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    edgeEdgeEnsembleCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(edgeEdgeEnsembleArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_surfaceVertexArraysCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    surfaceVertexArraysCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(surfaceVertexArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_surfaceEdgeArraysCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    surfaceEdgeArraysCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(surfaceEdgeArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_surfaceFaceArraysCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    surfaceFaceArraysCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(surfaceFaceArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_surfaceFaceFieldArraysCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    surfaceFaceFieldArraysCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(surfaceFaceFieldArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_surfaceFaceEnsembleArraysCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    surfaceFaceEnsembleArraysCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(surfaceFaceEnsembleArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_volumeVertexCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    volumeVertexCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(volumeVertexArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_volumeEdgeCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    volumeEdgeCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(volumeEdgeArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_volumeFaceCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    volumeFaceCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(volumeFaceArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_volumeCellCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    volumeCellCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(volumeCellArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_volumeCellFieldCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    volumeCellFieldCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(volumeCellFieldArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::on_volumeCellEnsembleCB_stateChanged(int state)
{
  if (state == Qt::PartiallyChecked) {
    volumeCellEnsembleCB->setCheckState(Qt::Checked);
    state = Qt::Checked;
  }
  toggleListSelections(volumeCellEnsembleArrayList, state);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::toggleListSelections(QListWidget* w, int state)
{

  w->blockSignals(true);
  int count = w->count();
  for(int i = 0; i < count; ++i)
  {
      w->item(i)->setCheckState(static_cast<Qt::CheckState>(state));
  }
  w->blockSignals(false);
  // Emit this signal so the preflight runs which will update all the guis after this one
  emit arrayListsChanged();
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::setSelections(QListWidget* listWidget, QStringList &selections)
{
  listWidget->blockSignals(true);
  int count = listWidget->count();
  for(int i = 0; i < count; ++i)
  {
    QString name = listWidget->item(i)->text();
    if (selections.contains(name) == true) {
      listWidget->item(i)->setCheckState(Qt::Checked);
    }
  }

  listWidget->blockSignals(false);
}


#define REMOVE_ARRAYS_HELPER(dtype, dataContainer, grouping, op)\
{QSet<QString> arrays = get##op##Arrays(dtype##grouping##ArrayList);\
  for(QSet<QString>::iterator iter = arrays.begin(); iter != arrays.end(); ++iter) {\
  dataContainer->remove##grouping##Data(*iter);\
  }}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::removeSelectionsFromDataContainers(DataContainerArray::Pointer dca)
{
  REMOVE_ARRAYS_HELPER(volume, vldc, Vertex, Selected)
  REMOVE_ARRAYS_HELPER(volume, vldc, Edge, Selected)
  REMOVE_ARRAYS_HELPER(volume, vldc, Face, Selected)
  REMOVE_ARRAYS_HELPER(volume, vldc, Cell, Selected)
  REMOVE_ARRAYS_HELPER(volume, vldc, CellField, Selected)
  REMOVE_ARRAYS_HELPER(volume, vldc, CellEnsemble, Selected)

  REMOVE_ARRAYS_HELPER(surface, sdc, Vertex, Selected)
  REMOVE_ARRAYS_HELPER(surface, sdc, Face, Selected)
  REMOVE_ARRAYS_HELPER(surface, sdc, Edge, Selected)
  REMOVE_ARRAYS_HELPER(surface, sdc, FaceField, Selected)
  REMOVE_ARRAYS_HELPER(surface, sdc, FaceEnsemble, Selected)

  REMOVE_ARRAYS_HELPER(edge, edc, Vertex, Selected)
  REMOVE_ARRAYS_HELPER(edge, edc, Edge, Selected)
  REMOVE_ARRAYS_HELPER(edge, edc, EdgeField, Selected)
  REMOVE_ARRAYS_HELPER(edge, edc, EdgeEnsemble, Selected)

  REMOVE_ARRAYS_HELPER(vertex, vdc, Vertex, Selected)
  REMOVE_ARRAYS_HELPER(vertex, vdc, VertexField, Selected)
  REMOVE_ARRAYS_HELPER(vertex, vdc, VertexEnsemble, Selected)
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::removeNonSelectionsFromDataContainers(DataContainerArray::Pointer dca)
{
  REMOVE_ARRAYS_HELPER(volume, vldc, Vertex, NonSelected)
  REMOVE_ARRAYS_HELPER(volume, vldc, Edge, NonSelected)
  REMOVE_ARRAYS_HELPER(volume, vldc, Face, NonSelected)
  REMOVE_ARRAYS_HELPER(volume, vldc, Cell, NonSelected)
  REMOVE_ARRAYS_HELPER(volume, vldc, CellField, NonSelected)
  REMOVE_ARRAYS_HELPER(volume, vldc, CellEnsemble, NonSelected)

  REMOVE_ARRAYS_HELPER(surface, sdc, Vertex, NonSelected)
  REMOVE_ARRAYS_HELPER(surface, sdc, Face, NonSelected)
  REMOVE_ARRAYS_HELPER(surface, sdc, Edge, NonSelected)
  REMOVE_ARRAYS_HELPER(surface, sdc, FaceField, NonSelected)
  REMOVE_ARRAYS_HELPER(surface, sdc, FaceEnsemble, NonSelected)

  REMOVE_ARRAYS_HELPER(edge, edc, Vertex, NonSelected)
  REMOVE_ARRAYS_HELPER(edge, edc, Edge, NonSelected)
  REMOVE_ARRAYS_HELPER(edge, edc, EdgeField, NonSelected)
  REMOVE_ARRAYS_HELPER(edge, edc, EdgeEnsemble, NonSelected)

  REMOVE_ARRAYS_HELPER(vertex, vdc, Vertex, NonSelected)
  REMOVE_ARRAYS_HELPER(vertex, vdc, VertexField, NonSelected)
  REMOVE_ARRAYS_HELPER(vertex, vdc, VertexEnsemble, NonSelected)
}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QSet<QString> ArraySelectionWidget::getSelectedArrays(QListWidget*listWidget)
{
  QSet<QString> selectedArrays;
  for(qint32 i = 0; i < listWidget->count(); ++i)
  {
    if (listWidget->item(i)->checkState() == Qt::Checked)
    {
      selectedArrays.insert(listWidget->item(i)->text());
    }
  }
  return selectedArrays;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::setSelectedArrays(QSet<QString> names, QListWidget*listWidget)
{
  if (names.isEmpty() == true)
  {
    return;
  }
  QSet<QString>::iterator iter = names.begin();
  for (; iter != names.end(); iter++)
  {
    for(qint32 i = 0; i < listWidget->count(); ++i)
    {
      if (listWidget->item(i)->text() == *iter)
      {
        listWidget->item(i)->setCheckState(Qt::Checked);
      }
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QSet<QString> ArraySelectionWidget::getNonSelectedArrays(QListWidget*listWidget)
{
  QSet<QString> non_selectedArrays;
  for(qint32 i = 0; i < listWidget->count(); ++i)
  {
    if (listWidget->item(i)->checkState() == Qt::Unchecked)
    {
      non_selectedArrays.insert(listWidget->item(i)->text());
    }
  }
  return non_selectedArrays;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::clearArraySelectionLists()
{
  volumeVertexArrayList->clear();
  volumeEdgeArrayList->clear();
  volumeFaceArrayList->clear();
  volumeCellArrayList->clear();
  volumeCellFieldArrayList->clear();
  volumeCellEnsembleArrayList->clear();

  surfaceVertexArrayList->clear();
  surfaceFaceArrayList->clear();
  surfaceEdgeArrayList->clear();
  surfaceFaceFieldArrayList->clear();
  surfaceFaceEnsembleArrayList->clear();

  edgeVertexArrayList->clear();
  edgeEdgeArrayList->clear();
  edgeEdgeFieldArrayList->clear();
  edgeEdgeEnsembleArrayList->clear();

  vertexVertexArrayList->clear();
  vertexVertexFieldArrayList->clear();
  vertexVertexEnsembleArrayList->clear();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::readOptions(QSettings &prefs, QString name)
{
  readSelections(prefs, name, "VolumeVertex", volumeVertexArrayList);
  readSelections(prefs, name, "VolumeEdge", volumeEdgeArrayList);
  readSelections(prefs, name, "VolumeFace", volumeFaceArrayList);
  readSelections(prefs, name, "VolumeCell", volumeCellArrayList);
  readSelections(prefs, name, "VolumeField", volumeCellFieldArrayList);
  readSelections(prefs, name, "VolumeEnsemble", volumeCellEnsembleArrayList);

  readSelections(prefs, name, "SurfaceVertex", surfaceVertexArrayList);
  readSelections(prefs, name, "SurfaceFace", surfaceFaceArrayList);
  readSelections(prefs, name, "SurfaceEdge", surfaceEdgeArrayList);
  readSelections(prefs, name, "SurfaceField", surfaceFaceFieldArrayList);
  readSelections(prefs, name, "SurfaceEnsemble", surfaceFaceEnsembleArrayList);

  readSelections(prefs, name, "EdgeVertex", edgeVertexArrayList);
  readSelections(prefs, name, "EdgeEdge", edgeEdgeArrayList);
  readSelections(prefs, name, "EdgeField", edgeEdgeFieldArrayList);
  readSelections(prefs, name, "EdgeEnsemble", edgeEdgeEnsembleArrayList);

  readSelections(prefs, name, "VertexVertex", vertexVertexArrayList);
  readSelections(prefs, name, "VertexField", vertexVertexFieldArrayList);
  readSelections(prefs, name, "VertexEnsemble", vertexVertexEnsembleArrayList);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::writeOptions(QSettings &prefs, QString name)
{
  writeSelections(prefs, name, "VolumeVertex", volumeVertexArrayList);
  writeSelections(prefs, name, "VolumeEdge", volumeEdgeArrayList);
  writeSelections(prefs, name, "VolumeFace", volumeFaceArrayList);
  writeSelections(prefs, name, "VolumeCell", volumeCellArrayList);
  writeSelections(prefs, name, "VolumeField", volumeCellFieldArrayList);
  writeSelections(prefs, name, "VolumeEnsemble", volumeCellEnsembleArrayList);

  writeSelections(prefs, name, "SurfaceVertex", surfaceVertexArrayList);
  writeSelections(prefs, name, "SurfaceFace", surfaceFaceArrayList);
  writeSelections(prefs, name, "SurfaceEdge", surfaceEdgeArrayList);
  writeSelections(prefs, name, "SurfaceField", surfaceFaceFieldArrayList);
  writeSelections(prefs, name, "SurfaceEnsemble", surfaceFaceEnsembleArrayList);

  writeSelections(prefs, name, "EdgeVertex", edgeVertexArrayList);
  writeSelections(prefs, name, "EdgeEdge", edgeEdgeArrayList);
  writeSelections(prefs, name, "EdgeField", edgeEdgeFieldArrayList);
  writeSelections(prefs, name, "EdgeEnsemble", edgeEdgeEnsembleArrayList);

  writeSelections(prefs, name, "VertexVertex", vertexVertexArrayList);
  writeSelections(prefs, name, "VertexField", vertexVertexFieldArrayList);
  writeSelections(prefs, name, "VertexEnsemble", vertexVertexEnsembleArrayList);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::writeSelections(QSettings &prefs, QString name, QString prefix, QListWidget* widget)
{

  QSet<QString> selections = getSelectedArrays(widget);
  int count = selections.size();
  prefs.beginWriteArray(name + "_" + prefix, count);
  count = 0;
  for(QSet<QString>::iterator iter = selections.begin(); iter != selections.end(); ++iter)
  {
    prefs.setArrayIndex(count++);
    prefs.setValue(prefix, (*iter));
  }
  prefs.endArray();
}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::readSelections(QSettings &prefs, QString name, QString prefix, QListWidget* widget)
{
  int count = prefs.beginReadArray(name + "_" + prefix);
  QStringList selections;
  for(int i = 0; i < count; ++i)
  {
    prefs.setArrayIndex(i);
    QString str = prefs.value(prefix, QString::fromUtf8("NOT_FOUND")).toString();
    selections.push_back(str);
  }
  prefs.endArray();
  populateArrayList(widget, selections);
  setSelections(widget, selections);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::setVolumeDataEnabled(bool b)
{
  volume_data->setEnabled(b);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::setSurfaceEnabled(bool b)
{
  surface_data->setEnabled(b);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::setEdgeEnabled(bool b)
{
  edge_data->setEnabled(b);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::setVertexEnabled(bool b)
{
  vertex_data->setEnabled(b);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::removeVolumeData()
{
  int index = indexOf(volume_data);
  removeTab(index);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::removeSurfaceData()
{
  int index = indexOf(surface_data);
  removeTab(index);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::removeEdgeData()
{
  int index = indexOf(edge_data);
  removeTab(index);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ArraySelectionWidget::removeVertexData()
{
  int index = indexOf(vertex_data);
  removeTab(index);
}
