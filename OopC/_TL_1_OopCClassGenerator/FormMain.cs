using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _TL_1_OopCClassGenerator
{
    public partial class FormMain : Form
    {
        private List<char> _TokenOptChar;

        public FormMain()
        {
            InitializeComponent();
            
            this.ActiveControl = this.BtnGenPath;
            this._TokenOptChar = new List<char>(new char[] { '_' });
            for (char c = 'a'; c <= 'z'; c++)
            {
                this._TokenOptChar.Add(c);
            }
            for (char c = 'A';  c <= 'Z'; c++)
            {
                this._TokenOptChar.Add(c);
            }
            for (char c = '0'; c <= '9'; c++)
            {
                this._TokenOptChar.Add(c);
            }
            
            this.BtnAddVariable.Tag = this.DgvVariables;
            this.BtnAddFunc.Tag = this.DgvFunctions;
            this.BtnDelVariable.Tag = this.DgvVariables;
            this.BtnDelFunc.Tag = this.DgvFunctions;
            this.ColPlaceholder.Visible = false;
        }

        private bool IsValidToken(string strName)
        {
            bool bValid = true;

            foreach (char c in strName)
            {
                if (!this._TokenOptChar.Contains(c))
                {
                    bValid = false;
                    break;
                }
            }

            if (strName[0] >= '0' && strName[0] <= '9')
            {
                bValid = false;
            }

            return bValid;
        }

        private bool GenHeader(ref string strErr)
        {
            string strPath = this.TxtBxPathHeader.Text.Trim();
            if (!strPath.EndsWith("\\"))
            {
                strPath += "\\";
            }
            FileStream fileStream = null;
            StreamWriter streamWriter = null;
            try
            {
                fileStream = new FileStream(strPath + this.TxtBxClassName.Text.Trim() + ".h", FileMode.Create, FileAccess.Write);
                if (fileStream == null)
                {
                    strErr = "创建文件流失败。";
                    return false;
                }
                streamWriter = new StreamWriter(fileStream);

                StringBuilder strContent = new StringBuilder();
                //License
                if (!string.IsNullOrEmpty(this.TxtBxLicense.Text.Trim()))
                {
                    strContent.Append(this.TxtBxLicense.Text.Trim());
                    strContent.AppendLine();
                    strContent.AppendLine();
                }
                //#ifndef条件编译宏
                strContent.AppendLine("#ifndef " + this.TxtBxClassName.Text.Trim().ToUpper() + "_H__");
                strContent.AppendLine("#define " + this.TxtBxClassName.Text.Trim().ToUpper() + "_H__");
                strContent.AppendLine();
                //父类头文件
                if (this.TxtBxInheritFrom.Text.Trim().Equals("Object"))
                {
                    strContent.AppendLine("#include <OopBase.h>");
                }
                else
                {
                    strContent.AppendLine("#include " + "\"" + this.TxtBxInheritFrom.Text.Trim() + ".h\"");
                }
                strContent.AppendLine();
                //CLASSDEF
                strContent.AppendLine("CLASSDEF(" + this.TxtBxClassName.Text.Trim() + ", " + this.TxtBxInheritFrom.Text.Trim() + ");");
                strContent.AppendLine();
                //Method
                for (int i = 0; i < DgvFunctions.Rows.Count; i++)
                {
                    bool bIsAbstract = (bool)DgvFunctions.Rows[i].Cells[1].EditedFormattedValue;
                    string strMethodName = DgvFunctions.Rows[i].Cells[2].Value.ToString().Trim();
                    strMethodName = strMethodName.Replace("\n", " ");
                    string strMethodParams = DgvFunctions.Rows[i].Cells[3].Value.ToString().Trim();
                    strMethodParams = strMethodParams.Replace("\n", " ");
                    if (string.IsNullOrEmpty(strMethodName))
                    {
                        strErr = "第" + (i + 1) + "行方法名称为空!";
                        streamWriter.Close();
                        fileStream.Close();
                        return false;
                    }

                    string strModifier = bIsAbstract ? "ABSTRACT " : "";
                    if (string.IsNullOrEmpty(strMethodParams))
                    {
                        strContent.AppendLine(strModifier + "typedef ParamNull " + this.TxtBxClassName.Text.Trim() + "_" + strMethodName + ";");
                    }
                    else
                    {
                        strContent.AppendLine(strModifier + "typedef struct { " + strMethodParams + " } " + this.TxtBxClassName.Text.Trim() + "_" + strMethodName + ";");
                    }
                }
                strContent.AppendLine();
                //#endif
                strContent.AppendLine("#endif // !" + this.TxtBxClassName.Text.Trim().ToUpper() + "_H__");

                streamWriter.Write(strContent.ToString());
                streamWriter.Flush();
                streamWriter.Close();
                fileStream.Close();

                return true;
            }
            catch (Exception ex)
            {
                strErr = ex.Message;
                return false;
            }
        }
        
        private bool GenSource(ref string strErr)
        {
            string strPath = this.TxtBxPathSource.Text.Trim();
            if (!strPath.EndsWith("\\"))
            {
                strPath += "\\";
            }
            FileStream fileStream = null;
            StreamWriter streamWriter = null;
            try
            {
                fileStream = new FileStream(strPath + this.TxtBxClassName.Text.Trim() + ".c", FileMode.Create, FileAccess.Write);
                if (fileStream == null)
                {
                    strErr = "打开文件流失败。";
                    return false;
                }
                streamWriter = new StreamWriter(fileStream);

                StringBuilder strContent = new StringBuilder();

                //License
                if (!string.IsNullOrEmpty(this.TxtBxLicense.Text.Trim()))
                {
                    strContent.AppendLine(this.TxtBxLicense.Text.Trim());
                    strContent.AppendLine();
                    strContent.AppendLine();
                }
                //include header
                strContent.AppendLine("#include \"" + this.TxtBxClassName.Text.Trim() + ".h\"");
                strContent.AppendLine();
                strContent.AppendLine();
                //field
                strContent.AppendLine("struct " + this.TxtBxClassName.Text.Trim());
                strContent.AppendLine("{");
                strContent.AppendLine("\tCHAINDEF;");
                strContent.AppendLine();
                for (int i = 0; i < DgvVariables.Rows.Count; i++)
                {
                    string strDataType = DgvVariables.Rows[i].Cells[2].Value.ToString().Trim();
                    string strName = DgvVariables.Rows[i].Cells[3].Value.ToString().Trim();
                    if (string.IsNullOrEmpty(strDataType) || string.IsNullOrEmpty(strName))
                    {
                        strErr = "第" + (i + 1) + "行为空!";
                        streamWriter.Close();
                        fileStream.Close();
                        return false;
                    }
                    strContent.AppendLine("\t" + strDataType + " " + strName + ";");
                }
                strContent.AppendLine("};");
                strContent.AppendLine();
                //分割
                strContent.AppendLine("/////////////////////////////////////////////////////////////////////////");
                strContent.AppendLine("//");
                strContent.AppendLine();
                //method
                string strMethodInCreate = "";
                for (int i = 0; i < DgvFunctions.Rows.Count; i++)
                {
                    bool bIsAbstract = (bool)DgvFunctions.Rows[i].Cells[1].EditedFormattedValue;
                    string strMethodName = DgvFunctions.Rows[i].Cells[2].Value.ToString().Trim();
                    strMethodName = strMethodName.Replace("\n", " ");
                    if (string.IsNullOrEmpty(strMethodName))
                    {
                        strErr = "第" + (i + 1) + "行方法名称为空!";
                        streamWriter.Close();
                        fileStream.Close();
                        return false;
                    }
                    if (!bIsAbstract)
                    {
                        strContent.AppendLine("static void " + strMethodName + "(void *pParams)");
                        strContent.AppendLine("{");
                        strContent.AppendLine("\t" + this.TxtBxClassName.Text.Trim() + " *pThis = ((ParamIn *)pParams)->pInst;");
                        strContent.AppendLine("\t" + this.TxtBxClassName.Text.Trim() + "_" + strMethodName + " *pIn = ((ParamIn *)pParams)->pIn;");
                        strContent.AppendLine();
                        strContent.AppendLine("\t//Todo: ");
                        strContent.AppendLine("}");
                    }

                    strMethodInCreate += "\t\t" + (bIsAbstract ? "A" : "") + "METHOD(" + strMethodName + ")\n";
                }
                strContent.AppendLine();
                //分割
                strContent.AppendLine("/////////////////////////////////////////////////////////////////////////");
                strContent.AppendLine("//");
                strContent.AppendLine();

                strContent.AppendLine("static void Clear(void *pParams)");
                strContent.AppendLine("{");
                strContent.AppendLine("\t" + this.TxtBxClassName.Text.Trim() + " *pInst = pParams;");
                strContent.AppendLine();
                strContent.AppendLine("\t//Todo: to release class extra mem.");
                strContent.AppendLine("}");
                strContent.AppendLine();
                //控制函数
                strContent.AppendLine("bool INVOKE(" + this.TxtBxClassName.Text.Trim() + ")(" + this.TxtBxClassName.Text.Trim() + " *pInst, char *pFuncName, void *pParams)");
                strContent.AppendLine("{");
                strContent.AppendLine("\tDOINVOKE(pInst, pFuncName, pParams);");
                strContent.AppendLine("}");
                strContent.AppendLine();
                strContent.AppendLine("void *EXTEND(" + this.TxtBxClassName.Text.Trim() + ")(" + this.TxtBxClassName.Text.Trim() + " *pInst)");
                strContent.AppendLine("{");
                strContent.AppendLine("\tDOEXTEND(pInst);");
                strContent.AppendLine("}");
                strContent.AppendLine();
                strContent.AppendLine("void DELETE(" + this.TxtBxClassName.Text.Trim() + ")(" + this.TxtBxClassName.Text.Trim() + " *pInst)");
                strContent.AppendLine("{");
                strContent.AppendLine("\tDODELETE(pInst, " + this.TxtBxClassName.Text.Trim() + ", " + this.TxtBxInheritFrom.Text.Trim() + ");");
                strContent.AppendLine("}");
                strContent.AppendLine();
                strContent.AppendLine(this.TxtBxClassName.Text.Trim() + " *CREATE(" + this.TxtBxClassName.Text.Trim() + ")()");
                strContent.AppendLine("{");
                if (string.IsNullOrEmpty(strMethodInCreate.Trim()))
                {
                    strContent.AppendLine("\tDOCREATE(pCreate, " + this.TxtBxClassName.Text.Trim() + ", " + this.TxtBxInheritFrom.Text.Trim() + ", " + "CLASSEXTRAMEM(Clear, pCreate));");
                }
                else
                {
                    strContent.AppendLine("\tDOCREATE(pCreate, " + this.TxtBxClassName.Text.Trim() + ", " + this.TxtBxInheritFrom.Text.Trim() + ", " + "CLASSEXTRAMEM(Clear, pCreate),");
                    strContent.AppendLine(strMethodInCreate.Substring(0, strMethodInCreate.Length - 1) + ");");
                }
                strContent.AppendLine();
                strContent.AppendLine("\treturn pCreate;");
                strContent.AppendLine("}");

                streamWriter.Write(strContent);
                streamWriter.Flush();
                streamWriter.Close();
                fileStream.Close();

                return true;
            }
            catch (Exception ex)
            {
                strErr = ex.Message;
                return false;
            }
        }

        private void BtnGenPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folderBrowser = new FolderBrowserDialog();

            folderBrowser.Description = "请选择类文件生成路径";
            folderBrowser.ShowNewFolderButton = true;

            if (!string.IsNullOrEmpty(this.TxtBxPathHeader.Text))
            {
                folderBrowser.SelectedPath = this.TxtBxPathHeader.Text;
            }

            if (folderBrowser.ShowDialog() == DialogResult.OK)
            {
                this.TxtBxPathHeader.Text = folderBrowser.SelectedPath + "\\";
                this.TxtBxPathSource.Text = folderBrowser.SelectedPath + "\\";
            }
        }

        private void TxtBxClassName_Leave(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            textBox.Text = textBox.Text.Trim();

            if (string.IsNullOrEmpty(textBox.Text))
            {
                return;
            }

            if (!this.IsValidToken(textBox.Text))
            {
                MessageBox.Show("不符合命名规则!");
                textBox.Focus();
            }
        }
        
        private void TxtBxInheritFrom_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            TextBox textBox = sender as TextBox;
            if (textBox.Tag == null)
            {
                textBox.Tag = new FormInherit();
            }

            FormInherit formInherit = textBox.Tag as FormInherit;
            formInherit.ShowDialog();
            textBox.Text = "<Super class>";
        }

        private void TxtBxLicense_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            FormLicense frmLicenseInputer = new FormLicense();
            frmLicenseInputer.LicenseContent = this.TxtBxLicense.Text;
            frmLicenseInputer.ShowDialog();
            this.TxtBxLicense.Text = frmLicenseInputer.LicenseContent;

            //this.TxtBxLicense.Text = this.TxtBxLicense.Text.Trim().Replace("\r\n", "\r\n//");
        }

        private void BtnAdd_Click(object sender, EventArgs e)
        {
            DataGridView dgv = (sender as Button).Tag as DataGridView;
            dgv.Rows.Add();
        }

        private void BtnDel_Click(object sender, EventArgs e)
        {
            DataGridView dgv = (sender as Button).Tag as DataGridView;
            for (int i = dgv.Rows.Count - 1; i >= 0; i--)
            {
                if ((bool)dgv.Rows[i].Cells[0].EditedFormattedValue)
                {
                    dgv.Rows.RemoveAt(i);
                }
            }
        }

        private void Dgv_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0 || e.ColumnIndex <= 1)
            {
                return;
            }

            DataGridView dgv = sender as DataGridView;

            FormCellContent frmCellContentInputer = new FormCellContent();
            frmCellContentInputer.CellContent = dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Tag != null ? dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Tag.ToString() : "";
            frmCellContentInputer.ShowDialog();
            dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Tag = frmCellContentInputer.CellContent;
            dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = frmCellContentInputer.CellContent.Replace('\n', ' ');
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("确认退出? 请注意保存内容。", "确认退出?", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
            {
                e.Cancel = true;
            }
        }

        private void BtnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void BtnGenFile_Click(object sender, EventArgs e)
        {
            //验证
            if (string.IsNullOrEmpty(this.TxtBxPathHeader.Text.Trim()) || string.IsNullOrEmpty(this.TxtBxPathSource.Text.Trim()))
            {
                MessageBox.Show("路径不能为空!");
                return;
            }
            if (string.IsNullOrEmpty(this.TxtBxClassName.Text.Trim()) || string.IsNullOrEmpty(this.TxtBxInheritFrom.Text.Trim()))
            {
                MessageBox.Show("类名不能为空!");
                return;
            }

            string strErr = "";
            if (!this.GenHeader(ref strErr))
            {
                MessageBox.Show("生成头文件失败: " + strErr);
                return;
            }
            if (!this.GenSource(ref strErr))
            {
                MessageBox.Show("生成源文件失败: " + strErr);
                return;
            }

            MessageBox.Show("生成成功! ^_^");
        }
    }
}
