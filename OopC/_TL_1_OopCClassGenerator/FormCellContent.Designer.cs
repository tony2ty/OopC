namespace _TL_1_OopCClassGenerator
{
    partial class FormCellContent
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
            this.TxtBxCellContent = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // TxtBxCellContent
            // 
            this.TxtBxCellContent.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TxtBxCellContent.Location = new System.Drawing.Point(0, 0);
            this.TxtBxCellContent.Multiline = true;
            this.TxtBxCellContent.Name = "TxtBxCellContent";
            this.TxtBxCellContent.Size = new System.Drawing.Size(466, 313);
            this.TxtBxCellContent.TabIndex = 0;
            // 
            // FormCellContent
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(466, 313);
            this.Controls.Add(this.TxtBxCellContent);
            this.Font = new System.Drawing.Font("YaHei Consolas Hybrid", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "FormCellContent";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "单元格内容";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox TxtBxCellContent;
    }
}