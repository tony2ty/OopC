using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _TL_1_OopCClassGenerator
{
    public partial class FormCellContent : Form
    {
        public string CellContent
        {
            set { this.TxtBxCellContent.Text = value; }
            get { return this.TxtBxCellContent.Text.Trim(); }
        }

        public FormCellContent()
        {
            InitializeComponent();
        }
    }
}
