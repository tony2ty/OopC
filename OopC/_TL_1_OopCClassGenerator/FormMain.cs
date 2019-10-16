using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _TL_1_OopCClassGenerator
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private bool IsValidPath(string strPath)
        {
            return !(strPath.IndexOfAny(Path.GetInvalidPathChars()) >= 0);
        }

        private bool IsValidFileName(string strName)
        {
            return !(strName.IndexOfAny(Path.GetInvalidFileNameChars()) >= 0);
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
    }
}
