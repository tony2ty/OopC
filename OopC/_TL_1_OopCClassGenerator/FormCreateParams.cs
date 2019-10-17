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
    public partial class FormCreateParams : Form
    {
        public string CreateParameters
        {
            set { this.TxtBxCreateParams.Text = value; }
            get { return this.TxtBxCreateParams.Text.Trim(); }
        }

        public FormCreateParams()
        {
            InitializeComponent();
            this.TxtBxCreateParams.Text = this.CreateParameters;
        }
    }
}
