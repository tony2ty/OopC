namespace _TL_1_OopCClassGenerator
{
    partial class FormMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.TxtBxPathHeader = new System.Windows.Forms.TextBox();
            this.BtnGenPath = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.TxtBxPathSource = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.TxtBxClassName = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.TxtBxInheritFrom = new System.Windows.Forms.TextBox();
            this.DgvVariables = new System.Windows.Forms.DataGridView();
            this.ColCheckedVar = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ColDataTypeVar = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColNameVar = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label8 = new System.Windows.Forms.Label();
            this.TxtBxCreateParam = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.DgvFunctions = new System.Windows.Forms.DataGridView();
            this.ColCheckedFunc = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ColIsAbstract = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ColRetTypeFunc = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColParameters = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label12 = new System.Windows.Forms.Label();
            this.TxtBxLicense = new System.Windows.Forms.TextBox();
            this.BtnDelVariable = new System.Windows.Forms.Button();
            this.BtnAddVariable = new System.Windows.Forms.Button();
            this.BtnDelFunc = new System.Windows.Forms.Button();
            this.BtnAddFunc = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.DgvVariables)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DgvFunctions)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label1.Font = new System.Drawing.Font("YaHei Consolas Hybrid", 25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(14, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(911, 52);
            this.label1.TabIndex = 0;
            this.label1.Text = "欢迎使用OopC类生成器";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 90);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(120, 16);
            this.label2.TabIndex = 1;
            this.label2.Text = "头文件(.h)路径：";
            // 
            // TxtBxPathHeader
            // 
            this.TxtBxPathHeader.Location = new System.Drawing.Point(138, 87);
            this.TxtBxPathHeader.Name = "TxtBxPathHeader";
            this.TxtBxPathHeader.Size = new System.Drawing.Size(653, 23);
            this.TxtBxPathHeader.TabIndex = 1;
            this.TxtBxPathHeader.Leave += new System.EventHandler(this.TxtBxPath_Leave);
            // 
            // BtnGenPath
            // 
            this.BtnGenPath.Location = new System.Drawing.Point(797, 87);
            this.BtnGenPath.Name = "BtnGenPath";
            this.BtnGenPath.Size = new System.Drawing.Size(75, 23);
            this.BtnGenPath.TabIndex = 3;
            this.BtnGenPath.Text = "生成路径";
            this.BtnGenPath.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.BtnGenPath.UseVisualStyleBackColor = true;
            this.BtnGenPath.Click += new System.EventHandler(this.BtnGenPath_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(19, 118);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(120, 16);
            this.label3.TabIndex = 1;
            this.label3.Text = "源文件(.c)路径：";
            // 
            // TxtBxPathSource
            // 
            this.TxtBxPathSource.Location = new System.Drawing.Point(138, 115);
            this.TxtBxPathSource.Name = "TxtBxPathSource";
            this.TxtBxPathSource.Size = new System.Drawing.Size(653, 23);
            this.TxtBxPathSource.TabIndex = 2;
            this.TxtBxPathSource.Leave += new System.EventHandler(this.TxtBxPath_Leave);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 162);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(64, 16);
            this.label4.TabIndex = 4;
            this.label4.Text = "类名称：";
            // 
            // label5
            // 
            this.label5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label5.Location = new System.Drawing.Point(12, 76);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(913, 2);
            this.label5.TabIndex = 6;
            this.label5.Text = "label5";
            // 
            // label6
            // 
            this.label6.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label6.Location = new System.Drawing.Point(12, 150);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(913, 2);
            this.label6.TabIndex = 7;
            this.label6.Text = "label6";
            // 
            // TxtBxClassName
            // 
            this.TxtBxClassName.Location = new System.Drawing.Point(103, 159);
            this.TxtBxClassName.Name = "TxtBxClassName";
            this.TxtBxClassName.Size = new System.Drawing.Size(219, 23);
            this.TxtBxClassName.TabIndex = 3;
            this.TxtBxClassName.Leave += new System.EventHandler(this.TxtBxClassName_Leave);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(19, 191);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(64, 16);
            this.label7.TabIndex = 4;
            this.label7.Text = "继承自：";
            // 
            // TxtBxInheritFrom
            // 
            this.TxtBxInheritFrom.Location = new System.Drawing.Point(103, 188);
            this.TxtBxInheritFrom.Name = "TxtBxInheritFrom";
            this.TxtBxInheritFrom.Size = new System.Drawing.Size(219, 23);
            this.TxtBxInheritFrom.TabIndex = 4;
            this.TxtBxInheritFrom.Leave += new System.EventHandler(this.TxtBxInheritFrom_Leave);
            // 
            // DgvVariables
            // 
            this.DgvVariables.AllowUserToAddRows = false;
            this.DgvVariables.AllowUserToDeleteRows = false;
            this.DgvVariables.AllowUserToResizeColumns = false;
            this.DgvVariables.AllowUserToResizeRows = false;
            this.DgvVariables.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
            this.DgvVariables.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DgvVariables.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColCheckedVar,
            this.ColDataTypeVar,
            this.ColNameVar});
            this.DgvVariables.Location = new System.Drawing.Point(22, 286);
            this.DgvVariables.Name = "DgvVariables";
            this.DgvVariables.RowTemplate.Height = 23;
            this.DgvVariables.Size = new System.Drawing.Size(903, 147);
            this.DgvVariables.TabIndex = 9;
            this.DgvVariables.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.Dgv_CellDoubleClick);
            // 
            // ColCheckedVar
            // 
            this.ColCheckedVar.HeaderText = "";
            this.ColCheckedVar.Name = "ColCheckedVar";
            // 
            // ColDataTypeVar
            // 
            this.ColDataTypeVar.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.White;
            this.ColDataTypeVar.DefaultCellStyle = dataGridViewCellStyle2;
            this.ColDataTypeVar.HeaderText = "成员类型";
            this.ColDataTypeVar.Name = "ColDataTypeVar";
            this.ColDataTypeVar.Width = 89;
            // 
            // ColNameVar
            // 
            this.ColNameVar.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.ColNameVar.HeaderText = "成员名称";
            this.ColNameVar.Name = "ColNameVar";
            this.ColNameVar.Width = 89;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(19, 220);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(78, 16);
            this.label8.TabIndex = 4;
            this.label8.Text = "构造参数：";
            // 
            // TxtBxCreateParam
            // 
            this.TxtBxCreateParam.BackColor = System.Drawing.SystemColors.Info;
            this.TxtBxCreateParam.Location = new System.Drawing.Point(103, 217);
            this.TxtBxCreateParam.Name = "TxtBxCreateParam";
            this.TxtBxCreateParam.Size = new System.Drawing.Size(219, 23);
            this.TxtBxCreateParam.TabIndex = 5;
            this.TxtBxCreateParam.Leave += new System.EventHandler(this.TxtBxCreateParam_Leave);
            this.TxtBxCreateParam.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.TxtBxCreateParam_MouseDoubleClick);
            // 
            // label9
            // 
            this.label9.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label9.Location = new System.Drawing.Point(12, 252);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(913, 2);
            this.label9.TabIndex = 7;
            this.label9.Text = "label6";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(19, 267);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(78, 16);
            this.label10.TabIndex = 4;
            this.label10.Text = "成员变量：";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(19, 447);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(78, 16);
            this.label11.TabIndex = 4;
            this.label11.Text = "成员方法：";
            // 
            // DgvFunctions
            // 
            this.DgvFunctions.AllowUserToAddRows = false;
            this.DgvFunctions.AllowUserToDeleteRows = false;
            this.DgvFunctions.AllowUserToResizeColumns = false;
            this.DgvFunctions.AllowUserToResizeRows = false;
            this.DgvFunctions.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
            this.DgvFunctions.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DgvFunctions.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColCheckedFunc,
            this.ColIsAbstract,
            this.ColRetTypeFunc,
            this.ColParameters});
            this.DgvFunctions.Location = new System.Drawing.Point(22, 466);
            this.DgvFunctions.Name = "DgvFunctions";
            this.DgvFunctions.RowTemplate.Height = 23;
            this.DgvFunctions.Size = new System.Drawing.Size(903, 147);
            this.DgvFunctions.TabIndex = 12;
            this.DgvFunctions.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.Dgv_CellDoubleClick);
            // 
            // ColCheckedFunc
            // 
            this.ColCheckedFunc.HeaderText = "";
            this.ColCheckedFunc.Name = "ColCheckedFunc";
            // 
            // ColIsAbstract
            // 
            this.ColIsAbstract.HeaderText = "抽象方法";
            this.ColIsAbstract.Name = "ColIsAbstract";
            // 
            // ColRetTypeFunc
            // 
            this.ColRetTypeFunc.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.ColRetTypeFunc.HeaderText = "返回值类型";
            this.ColRetTypeFunc.Name = "ColRetTypeFunc";
            this.ColRetTypeFunc.Width = 103;
            // 
            // ColParameters
            // 
            this.ColParameters.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.ColParameters.HeaderText = "方法参数";
            this.ColParameters.Name = "ColParameters";
            this.ColParameters.Width = 89;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(343, 162);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(78, 16);
            this.label12.TabIndex = 4;
            this.label12.Text = "开源证书：";
            // 
            // TxtBxLicense
            // 
            this.TxtBxLicense.BackColor = System.Drawing.SystemColors.Info;
            this.TxtBxLicense.Location = new System.Drawing.Point(427, 159);
            this.TxtBxLicense.Name = "TxtBxLicense";
            this.TxtBxLicense.Size = new System.Drawing.Size(219, 23);
            this.TxtBxLicense.TabIndex = 6;
            this.TxtBxLicense.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.TxtBxLicense_MouseDoubleClick);
            // 
            // BtnDelVariable
            // 
            this.BtnDelVariable.Location = new System.Drawing.Point(861, 263);
            this.BtnDelVariable.Name = "BtnDelVariable";
            this.BtnDelVariable.Size = new System.Drawing.Size(65, 23);
            this.BtnDelVariable.TabIndex = 8;
            this.BtnDelVariable.Text = "删除";
            this.BtnDelVariable.UseVisualStyleBackColor = true;
            this.BtnDelVariable.Click += new System.EventHandler(this.BtnDel_Click);
            // 
            // BtnAddVariable
            // 
            this.BtnAddVariable.Location = new System.Drawing.Point(790, 263);
            this.BtnAddVariable.Name = "BtnAddVariable";
            this.BtnAddVariable.Size = new System.Drawing.Size(65, 23);
            this.BtnAddVariable.TabIndex = 7;
            this.BtnAddVariable.Text = "新增";
            this.BtnAddVariable.UseVisualStyleBackColor = true;
            this.BtnAddVariable.Click += new System.EventHandler(this.BtnAdd_Click);
            // 
            // BtnDelFunc
            // 
            this.BtnDelFunc.Location = new System.Drawing.Point(861, 443);
            this.BtnDelFunc.Name = "BtnDelFunc";
            this.BtnDelFunc.Size = new System.Drawing.Size(65, 23);
            this.BtnDelFunc.TabIndex = 11;
            this.BtnDelFunc.Text = "删除";
            this.BtnDelFunc.UseVisualStyleBackColor = true;
            this.BtnDelFunc.Click += new System.EventHandler(this.BtnDel_Click);
            // 
            // BtnAddFunc
            // 
            this.BtnAddFunc.Location = new System.Drawing.Point(790, 443);
            this.BtnAddFunc.Name = "BtnAddFunc";
            this.BtnAddFunc.Size = new System.Drawing.Size(65, 23);
            this.BtnAddFunc.TabIndex = 10;
            this.BtnAddFunc.Text = "新增";
            this.BtnAddFunc.UseVisualStyleBackColor = true;
            this.BtnAddFunc.Click += new System.EventHandler(this.BtnAdd_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(820, 622);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(106, 38);
            this.button6.TabIndex = 13;
            this.button6.Text = "生  成";
            this.button6.UseVisualStyleBackColor = true;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(937, 669);
            this.Controls.Add(this.DgvFunctions);
            this.Controls.Add(this.DgvVariables);
            this.Controls.Add(this.TxtBxInheritFrom);
            this.Controls.Add(this.TxtBxLicense);
            this.Controls.Add(this.TxtBxCreateParam);
            this.Controls.Add(this.TxtBxClassName);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.BtnAddFunc);
            this.Controls.Add(this.BtnDelFunc);
            this.Controls.Add(this.BtnAddVariable);
            this.Controls.Add(this.BtnDelVariable);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.BtnGenPath);
            this.Controls.Add(this.TxtBxPathSource);
            this.Controls.Add(this.TxtBxPathHeader);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("YaHei Consolas Hybrid", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "OopC类生成器";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.DgvVariables)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DgvFunctions)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TxtBxPathHeader;
        private System.Windows.Forms.Button BtnGenPath;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox TxtBxPathSource;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox TxtBxClassName;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox TxtBxInheritFrom;
        private System.Windows.Forms.DataGridView DgvVariables;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox TxtBxCreateParam;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.DataGridView DgvFunctions;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox TxtBxLicense;
        private System.Windows.Forms.Button BtnDelVariable;
        private System.Windows.Forms.Button BtnAddVariable;
        private System.Windows.Forms.Button BtnDelFunc;
        private System.Windows.Forms.Button BtnAddFunc;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColCheckedVar;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColDataTypeVar;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColNameVar;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColCheckedFunc;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColIsAbstract;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColRetTypeFunc;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColParameters;
    }
}