#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <Windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <vector>
#include <memory>
#include "../inc/arxmodule.h"

class CCreateFieldMtext : public ITestCase
{
public:
  virtual const wchar_t* name() const
  {
    return L"Create a mtext with a field";
  }

  AcDbObjectId addMtext(IRoot* root)
  {
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();

    AcDbMtextPtr pMtext;
    pMtext.create();
    pMtext->setDatabaseDefaults(pDb);
    pMtext->setLocation(AcGePoint3d(10, 0, 0));
    pMtext->setContents(L"AAA");
    return root->addToModelSpace(pMtext);
  }

  virtual void run(IRoot* root)
  {
    AcDbMtextPtr pMtext(addMtext(root), AcDb::kForWrite);

    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();

    AcDbField* pSubField = new AcDbField;
    pSubField->setEvaluationOption(AcDbField::kAutomatic);
    pSubField->setFieldCode(L"\\AcVar Login", AcDbField::kFieldCode);
    pSubField->evaluate(AcDbField::kDemand, pDb);

    AcDbFieldArray fields;
    fields.append(pSubField);

    AcDbFieldPtr pField;
    pField.create();
    pField->setEvaluationOption(AcDbField::kAutomatic);
    pField->setInObject(pMtext, L"TEXT");

    AcString szFieldCode = L"%<\\_FldIdx 0>%ABC";
    szFieldCode = L"%<\\AcVar Login>%ABC";
    pField->setFieldCode(szFieldCode, AcDbField::FieldCodeFlag(AcDbField::kFieldCode | AcDbField::kTextField), &fields);
    pField->evaluate(AcDbField::kDemand, pDb);
  }
};

class CCreateLine : public ITestCase
{
public:
  virtual const wchar_t* name() const
  {
    return L"Create a line";
  }

  virtual void run(IRoot* root)
  {
    AcDbLinePtr pLine(createLine(root), AcDb::kForWrite);

    //   AcDbFieldPtr pSubField;
//   pSubField.create();
//   pSubField->setFieldCode(L"\\AcVar Login", AcDbField::kTextField);
// 
//   AcDbFieldArray fields;
//   fields.append(pSubField);

    AcDbFieldPtr pField;
    pField.create();
    pField->setFieldCode(L"\\AcVar Login", AcDbField::kFieldCode);
    //pField->setFieldCode(L"\\AcVar Login", AcDbField::kFieldCode, &fields);

    AcString strPropName = L"TEXT";
    AcDbObjectId fieldId;
    pLine->setField(strPropName, pField, fieldId);
  }

private:
  AcDbObjectId createLine(IRoot* root)
  {
    AcDbLinePtr pLine;
    pLine.create();
    pLine->setDatabaseDefaults();
    pLine->setStartPoint(AcGePoint3d(10, 0, 0));
    pLine->setEndPoint(AcGePoint3d(20, 10, 0));
    return root->addToModelSpace(pLine);
  }
};

class CListField : public ITestCase
{
public:
  virtual const wchar_t* name() const
  {
    return L"List all fields in an object";
  }

  virtual void run(IRoot* root)
  {
    ads_name entres;
    ads_point ptres;
    if (RTNORM != acedEntSel(L"\n选择一个带Field的实体：", entres, ptres))
    {
      root->printInfo(L"\n Failed to entsel.");
      return;
    }

    AcDbObjectId objId;
    acdbGetObjectId(objId, entres);

    AcDbEntityPointer pEnt(objId);
    if (Acad::eOk != pEnt.openStatus() || !pEnt->hasFields())
    {
      return;
    }

    AcDbDictionaryPointer pFieldDict(pEnt->getFieldDictionary());
    if (Acad::eOk != pFieldDict.openStatus())
    {
      root->printError(pFieldDict.openStatus(), L"getFieldDictionary");
      return;
    }

    std::unique_ptr<AcDbDictionaryIterator> iterator(pFieldDict->newIterator());
    while (!iterator->done())
    {
      acutPrintf(L"\n Name: %s", iterator->name());

      iterator->next();
    }
  }
};

class CReadField : public ITestCase
{
public:
  virtual const wchar_t* name() const
  {
    return L"Read the field info in an object";
  }

  virtual void run(IRoot* root)
  {
    ads_name entres;
    ads_point ptres;
    if (RTNORM != acedEntSel(L"\n选择一个带Field的实体：", entres, ptres))
    {
      root->printInfo(L"\n Failed to entsel.");
      return;
    }

    AcDbObjectId objId;
    acdbGetObjectId(objId, entres);

    AcDbEntityPointer pEnt(objId);
    if (Acad::eOk != pEnt.openStatus() || !pEnt->hasFields())
    {
      root->printError(pEnt.openStatus(), L"Failed to open an entity.");
      return;
    }

    AcDbDictionaryPointer pFieldDict(pEnt->getFieldDictionary());
    if (Acad::eOk != pFieldDict.openStatus())
    {
      root->printError(pFieldDict.openStatus(), L"Failed to get the field dictionary.");
      return;
    }

    std::unique_ptr<AcDbDictionaryIterator> iterator(pFieldDict->newIterator());
    while (!iterator->done())
    {
      AcDbFieldPtr pField(iterator->objectId());
      if (Acad::eOk == pField.openStatus())
      {
        printField(root, L"", pField);
      }

      iterator->next();
    }
  }

private:
  void printField(IRoot* root, const AcString& strTab, const AcDbFieldPtr& pField)
  {
    {
      //Acad::ErrorStatus setInObject(AcDbObject* pObj, const ACHAR * pszPropName);
      //Acad::ErrorStatus postInDatabase(AcDbDatabase* pDb);
    }
    {
      AcDbField::State state = pField->state();
      printState(root, strTab, state);
    }

    //   {
    //     int errCode = 0;
    //     AcString errMsg;
    //     AcDbField::EvalStatus status1 = pField->evaluationStatus(&errCode, &errMsg);
    //   }
    // 
    //   {
    //     AcDbField::EvalOption opt = pField->evaluationOption();
    //   }
    // 
    //   {
    //     AcDbField::EvalOption opt;
    //     Acad::ErrorStatus es = pField->setEvaluationOption(opt);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     AcDbField::FilingOption opt = pField->filingOption();
    //   }
    // 
    //   {
    //     AcDbField::FilingOption opt;
    //     Acad::ErrorStatus es = pField->setFilingOption(opt);
    //     printError(strTab, es);
    //   }

    {
      const ACHAR* szId = pField->evaluatorId();
      acutPrintf(L"\n%sevaluatorId: %s", strTab.constPtr(), szId);
    }

    //   {
    //     const ACHAR* szId;
    //     Acad::ErrorStatus es = pField->setEvaluatorId(szId);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     bool ret = pField->isTextField();
    //   }
    // 
    //   {
    //     Acad::ErrorStatus es = pField->convertToTextField();
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     AcDbField::FieldCodeFlag nFlag;
    //     AcArray<AcDbField*>* pChildFields = nullptr;
    //     AcDb::OpenMode mode = AcDb::kForRead;
    //     const ACHAR* ret = pField->getFieldCode(nFlag, pChildFields, mode);
    //   }

    {
      std::map<AcDbField::FieldCodeFlag, AcString> flags;
      flags[AcDbField::kFieldCode] = L"kFieldCode";
      flags[AcDbField::kEvaluatedText] = L"kEvaluatedText";
      flags[AcDbField::kEvaluatedChildren] = L"kEvaluatedChildren";
      flags[AcDbField::kObjectReference] = L"kObjectReference";
      flags[AcDbField::kAddMarkers] = L"kAddMarkers";
      flags[AcDbField::kEscapeBackslash] = L"kEscapeBackslash";
      flags[AcDbField::kStripOptions] = L"kStripOptions";
      flags[AcDbField::kPreserveFields] = L"kPreserveFields";
      flags[AcDbField::kTextField] = L"kTextField";
      flags[AcDbField::kPreserveOptions] = L"kPreserveOptions";
      flags[AcDbField::kDetachChildren] = L"kDetachChildren";
      flags[AcDbField::kChildObjectReference] = L"kChildObjectReference";
      flags[AcDbField::kForExpression] = L"kForExpression";

      for (auto& it : flags)
      {
        acutPrintf(L"\n%sgetFieldCode: %s", strTab.constPtr(), it.second.constPtr());
        getFieldCode(root, strTab + L"\t", pField, it.first);
      }
    }

    //   {
    //     const ACHAR* szFieldCode;
    //     AcDbField::FieldCodeFlag nFlag = (AcDbField::FieldCodeFlag) 0;
    //     AcDbFieldArray* pChildFields = NULL;
    //     Acad::ErrorStatus es = pField->setFieldCode(szFieldCode, nFlag, pChildFields);
    //     printError(strTab, es);
    //   }

  //   {
  //     int count = pField->childCount();
  //     acutPrintf(L"\n%schildCount: %d", strTab.constPtr(), count);
  //     AcString strSubTab = strTab + L"\t";
  //     for (int i = 0; i < count; i++)
  //     {
  //       acutPrintf(L"\n%s******Nth child[%d]******", strSubTab.constPtr(), i + 1);
  //       AcDbField* pSubField = nullptr;
  //       Acad::ErrorStatus es = pField->getChild(i, pSubField, AcDb::kForRead);
  //       if (Acad::eOk == es)
  //       {
  //         printField(strSubTab, pSubField);
  //         pSubField->close();
  //       }
  //       else
  //       {
  //         printError(strTab, es);
  //       }
  //     }
  //   }

    //   {
    //     const ACHAR* szFormat = pField->getFormat();
    //   }
    // 
    //   {
    //     AcString sFormat;
    //     Acad::ErrorStatus es = pField->getFormat(sFormat);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     const ACHAR* szFormat;
    //     Acad::ErrorStatus es = pField->setFormat(szFormat);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     int nContext;
    //     AcDbDatabase* pDb;
    //     int numFound = 0;
    //     int numEvaluated = 0;
    //     Acad::ErrorStatus es = pField->evaluate(nContext, pDb, &numFound, &numEvaluated);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     AcValue::DataType type = pField->dataType();
    //   }
    // 
    //   {
    //     const ACHAR* szValue = pField->getValue();
    //   }
    // 
    //   {
    //     AcString sValue;
    //     Acad::ErrorStatus es = pField->getValue(sValue);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     AcValue value;
    //     Acad::ErrorStatus es = pField->getValue(value);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     AcFdFieldValue value;
    //     Acad::ErrorStatus es = pField->getValue(value);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     bool ret = pField->hasHyperlink();
    //   }
    // 
    //   {
    //     AcHyperlink hlink;
    //     Acad::ErrorStatus es = pField->getHyperlink(hlink);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     AcString sName;
    //     AcString sDescription;
    //     AcString sSubLocation;
    //     AcString sDisplayString;
    //     Adesk::Int32 flag;
    //     Acad::ErrorStatus es = pField->getHyperlink(&sName, &sDisplayString, &sSubLocation, &sDisplayString, &flag);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     AcHyperlink hlink;
    //     Acad::ErrorStatus es = pField->setHyperlink(hlink);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     const ACHAR* szName;
    //     const ACHAR* szDescription;
    //     const ACHAR* szSubLocation = NULL;
    //     Acad::ErrorStatus es = pField->setHyperlink(szName, szDescription, szSubLocation);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     const ACHAR* szName;
    //     const ACHAR* szDescription;
    //     const ACHAR* szSubLocation;
    //     Adesk::Int32 lFlag;
    //     Acad::ErrorStatus es = pField->setHyperlink(szName, szDescription, szSubLocation, lFlag);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     Acad::ErrorStatus es = pField->removeHyperlink();
    //     printError(strTab, es);
    // 
    //   }
    // 
    //   {
    //     const ACHAR* szKey;
    //     AcValue data;
    //     Acad::ErrorStatus es = pField->getData(szKey, &data);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     const ACHAR* szKey;
    //     AcValue data;
    //     Acad::ErrorStatus es = pField->setData(szKey, &data);
    //     printError(strTab, es);
    //   }
    // 
    //   {
    //     const ACHAR* szKey;
    //     AcValue data;
    //     bool bRecursive;
    //     Acad::ErrorStatus es = pField->setData(szKey, &data, bRecursive);
    //     printError(strTab, es);
    //   }
  }

  void printState(IRoot* root, const AcString& strTab, AcDbField::State state)
  {
    AcString msg;
    msg.format(L"\n%sState(%d): ", strTab.constPtr(), state);
    root->printInfo(msg);
    if (state & AcDbField::kInitialized)
    {
      root->printInfo(L"kInitialized (Field has been initialized by the evaluator)");
    }
    if (state & AcDbField::kCompiled)
    {
      root->printInfo(L"kCompiled (Field has beene compiled)");
    }
    if (state & AcDbField::kModified)
    {
      root->printInfo(L"kModified (Field code has been modified, but not yet evaluated)");
    }
    if (state & AcDbField::kEvaluated)
    {
      root->printInfo(L"kEvaluated (Field has been evaluated)");
    }
    if (state & AcDbField::kHasCache)
    {
      root->printInfo(L"kHasCache (Field has evaluated cache)");
    }
    if (state & AcDbField::kHasFormattedString)
    {
      root->printInfo(L"kHasFormattedString (For internal use only. Field has cached formatted string. )");
    }
  }

  void getFieldCode(IRoot* root, const AcString& strTab, const AcDbFieldPtr& pField, AcDbField::FieldCodeFlag nFlag)
  {
    AcArray<AcDbField*> childFields;
    AcString sFieldCode = pField->getFieldCode(nFlag, &childFields, AcDb::kForRead);
    AcString msg;
    msg.format(L"\n%sgetFieldCode: %s  ChildFields: %d", strTab.constPtr(), sFieldCode.constPtr(), childFields.length());
    root->printInfo(msg);
    AcString strSubTab = strTab + L"\t";
    for (int i = 0; i < childFields.length(); i++)
    {
      msg.format(L"\n%s******Nth child[%d]******", strSubTab.constPtr(), i + 1);
      root->printInfo(msg);
      AcDbFieldPtr pSubField;
      pSubField.acquire(childFields[i]);
      printField(root, strSubTab, pSubField);
    }
  }
};

class CArxModule : public IArxModule
{
  std::vector<ITestCase*> m_cases;
public:
  CArxModule()
  {
    m_cases.push_back(new CCreateFieldMtext);
    //m_cases.push_back(new CCreateLine);
    //m_cases.push_back(new CListField);
    //m_cases.push_back(new CReadField);
  }
  ~CArxModule()
  {
    for (auto& it : m_cases)
    {
      delete it;
    }
  }

  virtual const wchar_t* moduleName() const
  {
    return L"Field test cases";
  }

  virtual int casesCount() const
  {
    return (int)m_cases.size();
  }

  virtual ITestCase* getCase(int i) const
  {
    return m_cases.at(i);
  }
};

extern "C" __declspec(dllexport) IArxModule* __stdcall arx_module()
{
  static CArxModule fieldModule;
  return &fieldModule;
}
