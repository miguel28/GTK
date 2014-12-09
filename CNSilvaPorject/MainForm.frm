VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.MDIForm MainForm 
   BackColor       =   &H8000000C&
   Caption         =   "CNSilva"
   ClientHeight    =   9150
   ClientLeft      =   165
   ClientTop       =   855
   ClientWidth     =   11745
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin MSComDlg.CommonDialog cdlSave 
      Left            =   1800
      Top             =   3120
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Menu mnu_File 
      Caption         =   "Archivo"
      Begin VB.Menu mnu_New 
         Caption         =   "Nuevo"
      End
      Begin VB.Menu mnu_Save 
         Caption         =   "Guardar"
      End
      Begin VB.Menu mnu_Exit 
         Caption         =   "Salir"
      End
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub mnu_Exit_Click()
End
End Sub

Private Sub mnu_New_Click()
NewFileWindow.Show
End Sub

Private Sub mnu_Save_Click()
cdlSave.ShowSave
  If cdlSave.FileName <> "" Then
    File = cdlSave.FileName
    Open File For Output As #1
    Print #1, StartProgram
    Print #1, Program
    Print #1, EndProgram
    Close #1
  End If
  Exit Sub
End Sub
