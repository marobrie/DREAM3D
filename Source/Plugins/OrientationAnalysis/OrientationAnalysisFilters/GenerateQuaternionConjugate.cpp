/*
 * Your License or Copyright can go here
 */

#include "GenerateQuaternionConjugate.h"

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/FilterParameters/BooleanFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArrayCreationFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"

#include "OrientationAnalysis/OrientationAnalysisConstants.h"
#include "OrientationAnalysis/OrientationAnalysisVersion.h"

#ifdef SIMPL_USE_PARALLEL_ALGORITHMS
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/partitioner.h>
#include <tbb/task_scheduler_init.h>
#endif

class GenerateQuaternionConjugateImpl
{
public:
  GenerateQuaternionConjugateImpl(GenerateQuaternionConjugate* filter, float* inputRod, float* outputRod)
  : m_Filter(filter)
  , m_Input(inputRod)
  , m_Output(outputRod)
  {
  }
  GenerateQuaternionConjugateImpl(const GenerateQuaternionConjugateImpl&) = default;           // Copy Constructor
  GenerateQuaternionConjugateImpl(GenerateQuaternionConjugateImpl&&) = delete;                 // Move Constructor Not Implemented
  GenerateQuaternionConjugateImpl& operator=(const GenerateQuaternionConjugateImpl&) = delete; // Copy Assignment Not Implemented
  GenerateQuaternionConjugateImpl& operator=(GenerateQuaternionConjugateImpl&&) = delete;      // Move Assignment Not Implemented

  virtual ~GenerateQuaternionConjugateImpl() = default;

  void convert(size_t start, size_t end) const
  {
    for(size_t i = start; i < end; i++)
    {
      if(m_Filter->getCancel())
      {
        return;
      }

      m_Output[i * 4] = -1.0f * m_Input[i * 4];
      m_Output[i * 4 + 1] = -1.0f * m_Input[i * 4 + 1];
      m_Output[i * 4 + 2] = -1.0f * m_Input[i * 4 + 2];
      m_Output[i * 4 + 3] = m_Input[i * 4 + 3];
    }
  }

#ifdef SIMPL_USE_PARALLEL_ALGORITHMS
  void operator()(const tbb::blocked_range<size_t>& r) const
  {
    convert(r.begin(), r.end());
  }
#endif
private:
  GenerateQuaternionConjugate* m_Filter = nullptr;
  float* m_Input;
  float* m_Output;
};

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenerateQuaternionConjugate::GenerateQuaternionConjugate()
: m_DeleteOriginalData(true)
{
  initialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenerateQuaternionConjugate::~GenerateQuaternionConjugate() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateQuaternionConjugate::initialize()
{
  setErrorCondition(0);
  setWarningCondition(0);
  setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateQuaternionConjugate::setupFilterParameters()
{
  FilterParameterVector parameters;
  DataArraySelectionFilterParameter::RequirementType dasReq;
  QVector<QVector<size_t>> comp;
  comp.push_back(QVector<size_t>(1, 4));
  dasReq.componentDimensions = comp;
  dasReq.daTypes = { SIMPL::TypeNames::Float };
  parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Quaternion Array", QuaternionDataArrayPath, FilterParameter::Parameter, GenerateQuaternionConjugate, dasReq));
  DataArrayCreationFilterParameter::RequirementType dacReq;
  parameters.push_back(SIMPL_NEW_DA_CREATION_FP("Output Data Array Path", OutputDataArrayPath, FilterParameter::CreatedArray, GenerateQuaternionConjugate, dacReq));
  parameters.push_back(SIMPL_NEW_BOOL_FP("Delete Original Data", DeleteOriginalData, FilterParameter::Parameter, GenerateQuaternionConjugate));
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateQuaternionConjugate::dataCheck()
{
  setErrorCondition(0);
  setWarningCondition(0);

  QVector<size_t> cDims(1, 1);
  cDims[0] = 4;
  m_QuaternionsPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<float>, AbstractFilter>(this, getQuaternionDataArrayPath(), cDims);
  if(nullptr != m_QuaternionsPtr.lock())
  {
    m_Quaternions = m_QuaternionsPtr.lock()->getPointer(0);
  }

  cDims[0] = 4;
  m_OutputQuaternionsPtr = getDataContainerArray()->createNonPrereqArrayFromPath<DataArray<float>, AbstractFilter, float>(
      this, getOutputDataArrayPath(), 0, cDims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if(nullptr != m_OutputQuaternionsPtr.lock())
  {
    m_OutputQuaternions = m_OutputQuaternionsPtr.lock()->getPointer(0);
  }

  if(getDeleteOriginalData() && getInPreflight())
  {
    AttributeMatrix::Pointer am = getDataContainerArray()->getAttributeMatrix(getQuaternionDataArrayPath());
    if(am)
    {
      am->removeAttributeArray(getQuaternionDataArrayPath().getDataArrayName());
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateQuaternionConjugate::preflight()
{
  // These are the REQUIRED lines of CODE to make sure the filter behaves correctly
  setInPreflight(true);              // Set the fact that we are preflighting.
  emit preflightAboutToExecute();    // Emit this signal so that other widgets can do one file update
  emit updateFilterParameters(this); // Emit this signal to have the widgets push their values down to the filter
  dataCheck();                       // Run our DataCheck to make sure everthing is setup correctly
  emit preflightExecuted();          // We are done preflighting this filter
  setInPreflight(false);             // Inform the system this filter is NOT in preflight mode anymore.
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateQuaternionConjugate::execute()
{
  initialize();
  dataCheck();
  if(getErrorCondition() < 0)
  {
    return;
  }

  size_t totalPoints = m_QuaternionsPtr.lock()->getNumberOfTuples();

#ifdef SIMPL_USE_PARALLEL_ALGORITHMS
  tbb::task_scheduler_init init;
  bool doParallel = true;
#endif

#ifdef SIMPL_USE_PARALLEL_ALGORITHMS
  if(doParallel)
  {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, totalPoints), GenerateQuaternionConjugateImpl(this, m_Quaternions, m_OutputQuaternions), tbb::auto_partitioner());
  }
  else
#endif
  {
    GenerateQuaternionConjugateImpl serial(this, m_Quaternions, m_OutputQuaternions);
    serial.convert(0, totalPoints);
  }

  /* Do not forget to remove the original array if requested */
  if(getDeleteOriginalData())
  {
    getDataContainerArray()->getAttributeMatrix(getQuaternionDataArrayPath())->removeAttributeArray(getQuaternionDataArrayPath().getDataArrayName());
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer GenerateQuaternionConjugate::newFilterInstance(bool copyFilterParameters) const
{
  GenerateQuaternionConjugate::Pointer filter = GenerateQuaternionConjugate::New();
  if(copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString GenerateQuaternionConjugate::getCompiledLibraryName() const
{
  return OrientationAnalysisConstants::OrientationAnalysisBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString GenerateQuaternionConjugate::getBrandingString() const
{
  return "OrientationAnalysis";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString GenerateQuaternionConjugate::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << OrientationAnalysis::Version::Major() << "." << OrientationAnalysis::Version::Minor() << "." << OrientationAnalysis::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString GenerateQuaternionConjugate::getGroupName() const
{
  return SIMPL::FilterGroups::ProcessingFilters;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString GenerateQuaternionConjugate::getSubGroupName() const
{
  return SIMPL::FilterSubGroups::CrystallographyFilters;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString GenerateQuaternionConjugate::getHumanLabel() const
{
  return "Generate Quaternion Conjugate";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QUuid GenerateQuaternionConjugate::getUuid()
{
  return QUuid("{630d7486-75ea-5e04-874c-894460cd7c4d}");
}
