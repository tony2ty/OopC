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
        private string _CreateParams;
        private List<char> _TokenOptChar;

        public FormMain()
        {
            InitializeComponent();
            
            this.ActiveControl = this.BtnGenPath;
            this.TxtBxInheritFrom.Text = "Object";
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

            this._CreateParams = "";
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

        private void TxtBxPath_Leave(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            textBox.Text = textBox.Text.Trim();

            if (string.IsNullOrEmpty(textBox.Text))
            {
                return;
            }

            if (!Directory.Exists(textBox.Text))
            {
                if (MessageBox.Show("指定的路径不存在，是否创建该路径?", "路径不存在", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                {
                    try
                    {
                        Directory.CreateDirectory(textBox.Text);
                        return;
                    }
                    catch
                    {
                        MessageBox.Show("无法创建指定的路径，请检查该路径是否正确，或者是否过长。");
                    }
                }

                //else
                //error when create directory
                textBox.Focus();
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

        private void TxtBxInheritFrom_Leave(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            textBox.Text = textBox.Text.Trim();

            if (string.IsNullOrEmpty(textBox.Text))
            {
                MessageBox.Show("继承的类类型名称的不能为空!");
                textBox.Focus();
            }

            if (!this.IsValidToken(textBox.Text))
            {
                MessageBox.Show("不符合命名规则!");
                textBox.Focus();
            }
        }

        private void TxtBxCreateParam_Leave(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            textBox.Text = textBox.Text.Trim();

            if (string.IsNullOrEmpty(textBox.Text))
            {
                return;
            }

            string[] strTokens = textBox.Text.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            List<string> lstTokens = new List<string>(strTokens);
            for (int i = lstTokens.Count - 1; i >= 0; i--)
            {
                if (lstTokens[i].Equals(","))
                {
                    lstTokens.RemoveAt(i);
                }
            }
            
            foreach (string token in lstTokens)
            {
                if (!this.IsValidToken(token))
                {
                    textBox.Focus();
                    break;
                }
            }
        }

        private void TxtBxCreateParam_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            FormCreateParams frmCreateParamsInputer = new FormCreateParams();
            frmCreateParamsInputer.CreateParameters = this._CreateParams;
            frmCreateParamsInputer.ShowDialog();
            this._CreateParams = frmCreateParamsInputer.CreateParameters;
            this.TxtBxCreateParam.Text = frmCreateParamsInputer.CreateParameters.Replace('\n', ' ');
        }

        private void TxtBxLicense_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            FormLicense frmLicenseInputer = new FormLicense();
            frmLicenseInputer.LicenseContent = this.TxtBxLicense.Text;
            frmLicenseInputer.ShowDialog();
            this.TxtBxLicense.Text = frmLicenseInputer.LicenseContent;
        }
    }
}
