/***************************************************************************
 *   Copyright (c) 2015 FreeCAD Developers                                 *
 *   Author: Przemo Firszt <przemo@firszt.eu>                              *
 *   Based on src/Mod/Raytracing/Gui/DlgSettingsRayImp.cpp                 *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "PreCompiled.h"

#include <App/Application.h>

#include "DlgSettingsFemGeneralImp.h"
#include "ui_DlgSettingsFemGeneral.h"


using namespace FemGui;

DlgSettingsFemGeneralImp::DlgSettingsFemGeneralImp(QWidget* parent)
    : PreferencePage(parent)
    , ui(new Ui_DlgSettingsFemGeneralImp)
{
    ui->setupUi(this);

    // fill solvers combo with available solvers
    ui->cmb_def_solver->clear();
    std::vector<std::string> Solvers = {"None"};

    ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath(
        "User parameter:BaseApp/Preferences/Mod/Fem/Ccx");
    auto ccxBinaryPath = hGrp->GetASCII("ccxBinaryPath", "");
    if (!ccxBinaryPath.empty())
        Solvers.push_back("CalculiX");
    hGrp = App::GetApplication().GetParameterGroupByPath(
        "User parameter:BaseApp/Preferences/Mod/Fem/Elmer");
    auto elmerBinaryPath = hGrp->GetASCII("elmerBinaryPath", "");
    if (!elmerBinaryPath.empty())
        Solvers.push_back("Elmer");
    hGrp = App::GetApplication().GetParameterGroupByPath(
        "User parameter:BaseApp/Preferences/Mod/Fem/mystran");
    auto MystranBinaryPath = hGrp->GetASCII("MystranBinaryPath", "");
    if (!MystranBinaryPath.empty())
        Solvers.push_back("Mystran");
    hGrp = App::GetApplication().GetParameterGroupByPath(
        "User parameter:BaseApp/Preferences/Mod/Fem/Z88");
    auto z88BinaryPath = hGrp->GetASCII("z88BinaryPath", "");
    if (!z88BinaryPath.empty())
        Solvers.push_back("Z88");

    QStringList solversList;
    for (auto item : Solvers) {
        solversList << QLatin1String(item.c_str());
    }
    ui->cmb_def_solver->addItems(solversList);
}

DlgSettingsFemGeneralImp::~DlgSettingsFemGeneralImp()
{
    // no need to delete child widgets, Qt does it all for us
}

void DlgSettingsFemGeneralImp::saveSettings()
{
    ui->cb_analysis_group_meshing->onSave();

    ui->cb_restore_result_dialog->onSave();
    ui->cb_keep_results_on_rerun->onSave();
    ui->cb_hide_constraint->onSave();

    ui->cb_wd_temp->onSave();
    ui->cb_wd_beside->onSave();
    ui->cb_wd_custom->onSave();
    ui->le_wd_custom->onSave();
    ui->cb_overwrite_solver_working_directory->onSave();
    ui->cmb_def_solver->onSave();
}

void DlgSettingsFemGeneralImp::loadSettings()
{
    ui->cb_analysis_group_meshing->onRestore();

    ui->cb_restore_result_dialog->onRestore();
    ui->cb_keep_results_on_rerun->onRestore();
    ui->cb_hide_constraint->onRestore();

    ui->cb_wd_temp->onRestore();
    ui->cb_wd_beside->onRestore();
    ui->cb_wd_custom->onRestore();
    ui->le_wd_custom->onRestore();
    ui->cb_overwrite_solver_working_directory->onRestore();
    ui->cmb_def_solver->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsFemGeneralImp::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsFemGeneralImp.cpp"
