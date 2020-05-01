#ifndef INSTALLERFOMOD_H
#define INSTALLERFOMOD_H


#include <iplugininstallersimple.h>
#include <iplugindiagnose.h>
#include <ipluginlist.h>


class InstallerFomod : public MOBase::IPluginInstallerSimple, public MOBase::IPluginDiagnose
{

  Q_OBJECT
  Q_INTERFACES(MOBase::IPlugin MOBase::IPluginInstaller MOBase::IPluginInstallerSimple MOBase::IPluginDiagnose)
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  Q_PLUGIN_METADATA(IID "org.tannin.InstallerFomod" FILE "installerfomod.json")
#endif

public:

  InstallerFomod();

  virtual bool init(MOBase::IOrganizer *moInfo);
  virtual QString name() const;
  virtual QString author() const;
  virtual QString description() const;
  virtual MOBase::VersionInfo version() const;
  virtual bool isActive() const;
  virtual QList<MOBase::PluginSetting> settings() const;

  virtual unsigned int priority() const;
  virtual bool isManualInstaller() const;

  virtual bool isArchiveSupported(std::shared_ptr<const MOBase::IFileTree> tree) const;
  virtual EInstallResult install(MOBase::GuessedValue<QString> &modName, std::shared_ptr<MOBase::IFileTree>&tree,
                                 QString &version, int &modID);

public: // IPluginDiagnose interface

  virtual std::vector<unsigned int> activeProblems() const;
  virtual QString shortDescription(unsigned int key) const;
  virtual QString fullDescription(unsigned int key) const;
  virtual bool hasGuidedFix(unsigned int key) const;
  virtual void startGuidedFix(unsigned int key) const;

private:

  /**
   * @brief Retrieve the tree entry corresponding to the fomod directory.
   *
   * @param tree Tree to look-up the directory in.
   *
   * @return the entry corresponding to the fomod directory in the tree, or a null pointer if the entry was not found.
   */
  std::shared_ptr<const MOBase::IFileTree> findFomodDirectory(std::shared_ptr<const MOBase::IFileTree> tree) const;

  /**
   * @brief Build a list of entries that should be extracted sincce the FOMOD installer may require access 
   *     to (currently the .xml files in the FOMOD directory and the pictures in the archive).
   *
   * @param tree Base tree of the archive.
   *
   * @return a list of file entries that need to be extracted.
   */
  std::vector<std::shared_ptr<const MOBase::FileTreeEntry>> buildFomodTree(std::shared_ptr<const MOBase::IFileTree> tree) const;

  /**
   * @brief Recurse through the given tree and add all the images to the given vector.
   *
   * @param result Vector of entries to add the images.
   * @param tree The tree to look files in.
   */
  void appendImageFiles(
    std::vector<std::shared_ptr<const MOBase::FileTreeEntry>> &entries, std::shared_ptr<const MOBase::IFileTree> tree) const;

  MOBase::IPluginList::PluginStates fileState(const QString &fileName) const;

private:

  static const unsigned int PROBLEM_IMAGETYPE_UNSUPPORTED = 1;

private:

  MOBase::IOrganizer *m_MOInfo;

  bool allowAnyFile() const;
  bool checkDisabledMods() const;
};

#endif // INSTALLERFOMOD_H
