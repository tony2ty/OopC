﻿using System;
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
    public partial class FormLicense : Form
    {
        public string LicenseContent
        {
            set { this.TxtBxLicense.Text = value; }
            get { return this.TxtBxLicense.Text.Trim(); }
        }

        public FormLicense()
        {
            InitializeComponent();
        }
    }
}
