#ifndef _FilterParameterWidgetUtils_H_
#define _FilterParameterWidgetUtils_H_

#include <QtCore/QString>
#include <QtWidgets/QComboBox>
#include <QtGui/QStandardItemModel>

#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/DataContainers/DataContainerArray.h"
#include "DREAM3DLib/DataContainers/DataContainerArrayProxy.h"
#include "DREAM3DLib/DataContainers/DataContainerProxy.h"
#include "DREAM3DLib/FilterParameters/FilterParameter.h"




class FilterPararameterWidgetUtils
{
  public:

    template<typename FilterParameterType>
    static void PopulateDataContainerComboBox(AbstractFilter* filter, FilterParameter* filterParameter,
                                              QComboBox* dcCombo, DataContainerArrayProxy& dcaProxy)
    {
      FilterParameterType* fp = dynamic_cast<FilterParameterType*>(filterParameter);
      assert(fp != NULL);
      DataContainerArray::Pointer dca = filter->getDataContainerArray();
      // Populate the DataContainerArray Combo Box with all the DataContainers
      QList<DataContainerProxy> dcList = dcaProxy.dataContainers.values();
      QListIterator<DataContainerProxy> iter(dcList);
      dcCombo->clear();
      QVector<unsigned int> defVec = fp->getDefaultGeometryTypes();
      while(iter.hasNext() )
      {
        DataContainerProxy dcProxy = iter.next();
        DataContainer::Pointer dc = dca->getDataContainer(dcProxy.name);
        dcCombo->addItem(dcProxy.name);

        if (NULL != dc.get() && defVec.isEmpty() == false && defVec.contains(dc->getGeometry()->getGeometryType()) == false)
        {
          QStandardItemModel* model = qobject_cast<QStandardItemModel*>(dcCombo->model());
          if (NULL != model)
          {
            QStandardItem* item = model->item(dcCombo->findText(dcProxy.name));
            if (NULL != item)
            {
              item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            }
          }
        }
      }

    }




    template<typename FilterParameterType>
    static void PopulateAttributeMatrixComboBox(AbstractFilter* filter, FilterParameter* filterParameter,
                                            QComboBox* dcCombo, QComboBox* amCombo,
                                            DataContainerArrayProxy& dcaProxy)
    {
      FilterParameterType* fp = dynamic_cast<FilterParameterType*>(filterParameter);
      assert(fp != NULL);
      DataContainerArray::Pointer dca = filter->getDataContainerArray();
      if (NULL == dca.get()) { return; }

      QString dcName = dcCombo->currentText();

      // Clear the AttributeMatrix List
      bool alreadyBlocked = false;
      if(amCombo->signalsBlocked()) { alreadyBlocked = true; }
      amCombo->blockSignals(true);
      amCombo->clear();

      // Loop over the data containers until we find the proper data container
      QList<DataContainerProxy> containers = dcaProxy.dataContainers.values();
      QListIterator<DataContainerProxy> containerIter(containers);
      QVector<unsigned int> defVec = fp->getDefaultAttributeMatrixTypes();
      while(containerIter.hasNext())
      {
        DataContainerProxy dc = containerIter.next();

        if(dc.name.compare(dcName) == 0 )
        {
          // We found the proper Data Container, now populate the AttributeMatrix List
          QMap<QString, AttributeMatrixProxy> attrMats = dc.attributeMatricies;
          QMapIterator<QString, AttributeMatrixProxy> attrMatsIter(attrMats);
          while(attrMatsIter.hasNext() )
          {
            attrMatsIter.next();
            QString amName = attrMatsIter.key();
            AttributeMatrix::Pointer am = dca->getAttributeMatrix(DataArrayPath(dc.name, amName, ""));
            amCombo->addItem(amName);

            if (NULL != am.get() && defVec.isEmpty() == false && defVec.contains(am->getType()) == false)
            {
              QStandardItemModel* model = qobject_cast<QStandardItemModel*>(amCombo->model());
              if (NULL != model)
              {
                QStandardItem* item = model->item(amCombo->findText(amName));
                if (NULL != item)
                {
                  item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
                }
              }
            }
          }
        }
      }

      if(!alreadyBlocked) { // Only unblock if this function blocked the signals.
        amCombo->blockSignals(false);
      }
    }



    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    template<typename FilterParameterType>
    static void PopulateAttributeArrayComboBox(AbstractFilter* filter, FilterParameter* filterParameter,
                                      QComboBox* dcCombo, QComboBox* amCombo, QComboBox* aaCombo,
                                      DataContainerArrayProxy& dcaProxy)
    {
      FilterParameterType* fp = dynamic_cast<FilterParameterType*>(filterParameter);
      assert(fp != NULL);

      DataContainerArray::Pointer dca = filter->getDataContainerArray();
      if (NULL == dca.get()) { return; }
      bool alreadyBlocked = false;
      if(aaCombo->signalsBlocked()) { alreadyBlocked = true; }
      aaCombo->blockSignals(true);
      aaCombo->clear();

      // Get the selected Data Container Name from the DataContainerList Widget
      QString currentDCName = dcCombo->currentText();
      QString currentAttrMatName = amCombo->currentText();

      // Loop over the data containers until we find the proper data container
      QList<DataContainerProxy> containers = dcaProxy.dataContainers.values();
      QListIterator<DataContainerProxy> containerIter(containers);
      QVector<QString> daTypes = fp->getDefaultAttributeArrayTypes();
      QVector< QVector<size_t> > cDims = fp->getDefaultComponentDimensions();
      while (containerIter.hasNext())
      {
        DataContainerProxy dc = containerIter.next();
        if (dc.name.compare(currentDCName) == 0)
        {
          // We found the proper Data Container, now populate the AttributeMatrix List
          QMap<QString, AttributeMatrixProxy> attrMats = dc.attributeMatricies;
          QMapIterator<QString, AttributeMatrixProxy> attrMatsIter(attrMats);
          while (attrMatsIter.hasNext())
          {
            attrMatsIter.next();
            QString amName = attrMatsIter.key();
            if (amName.compare(currentAttrMatName) == 0)
            {
              // Clear the list of arrays from the QListWidget
              aaCombo->clear();
              // We found the selected AttributeMatrix, so loop over this attribute matrix arrays and populate the list widget
              AttributeMatrixProxy amProxy = attrMatsIter.value();
              QMap<QString, DataArrayProxy> dataArrays = amProxy.dataArrays;
              QMapIterator<QString, DataArrayProxy> dataArraysIter(dataArrays);
              while (dataArraysIter.hasNext())
              {
                dataArraysIter.next();
                //DataArrayProxy daProxy = dataArraysIter.value();
                QString daName = dataArraysIter.key();
                IDataArray::Pointer da = dca->getPrereqIDataArrayFromPath<IDataArray, AbstractFilter>(NULL, DataArrayPath(dc.name, amProxy.name, daName));
                aaCombo->addItem(daName);

                if (NULL != da.get() && ((daTypes.isEmpty() == false && daTypes.contains(da->getTypeAsString()) == false) || (cDims.isEmpty() == false && cDims.contains(da->getComponentDimensions()) == false)))
                {
                  QStandardItemModel* model = qobject_cast<QStandardItemModel*>(aaCombo->model());
                  if (NULL != model)
                  {
                    QStandardItem* item = model->item(aaCombo->findText(daName));
                    if (NULL != item)
                    {
                      item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
                    }
                  }
                }
              }
            }
          }
        }

        aaCombo->setCurrentIndex(-1);
        if(alreadyBlocked == false)
        {
          aaCombo->blockSignals(false);
        }
      }
    }



  protected:
    FilterPararameterWidgetUtils() {}

  private:

};

#endif /* _FilterParameterWidgetUtils_H_ */