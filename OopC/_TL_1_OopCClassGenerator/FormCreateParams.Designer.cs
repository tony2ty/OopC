namespace _TL_1_OopCClassGenerator
{
    partial class FormCreateParams
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
            this.TxtBxCreateParams = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // TxtBxCreateParams
            // 
            this.TxtBxCreateParams.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TxtBxCreateParams.Location = new System.Drawing.Point(0, 0);
            this.TxtBxCreateParams.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.TxtBxCreateParams.Multiline = true;
            this.TxtBxCreateParams.Name = "TxtBxCreateParams";
            this.TxtBxCreateParams.Size = new System.Drawing.Size(375, 254);
            this.TxtBxCreateParams.TabIndex = 0;
            // 
            // FormCreateParams
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(375, 254);
            this.Controls.Add(this.TxtBxCreateParams);
            this.Font = new System.Drawing.Font("YaHei Consolas Hybrid", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "FormCreateParams";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "构造参数";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox TxtBxCreateParams;
    }
}