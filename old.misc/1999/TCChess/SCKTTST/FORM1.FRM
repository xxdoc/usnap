VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form Form1 
   Caption         =   "������"
   ClientHeight    =   4215
   ClientLeft      =   2265
   ClientTop       =   1905
   ClientWidth     =   4905
   LinkTopic       =   "Form1"
   ScaleHeight     =   4215
   ScaleWidth      =   4905
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   6000
      Left            =   4320
      Top             =   3120
   End
   Begin VB.CommandButton Send 
      Caption         =   "����"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   372
      Left            =   3240
      TabIndex        =   5
      Top             =   1800
      Width           =   1092
   End
   Begin VB.CommandButton Comm2 
      Caption         =   "����"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   372
      Left            =   3240
      TabIndex        =   4
      Top             =   960
      Width           =   1092
   End
   Begin VB.CommandButton Comm1 
      Caption         =   "�˳�"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   372
      Left            =   3240
      TabIndex        =   3
      Top             =   480
      Width           =   1092
   End
   Begin VB.ComboBox Combo1 
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1920
      TabIndex        =   2
      Text            =   "10.84.234.11"
      Top             =   3120
      Width           =   1812
   End
   Begin VB.TextBox Text2 
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1092
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   1
      Text            =   "FORM1.frx":0000
      Top             =   600
      Width           =   3012
   End
   Begin VB.TextBox Text1 
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Text            =   "FORM1.frx":0009
      Top             =   2040
      Width           =   3012
   End
   Begin MSWinsockLib.Winsock a 
      Left            =   2520
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
      RemoteHost      =   "�ҿ���ҵ"
   End
   Begin VB.Label Label5 
      Caption         =   "����: ѡ��ַ����, ���ӳɹ��󿴵����������ݺ�������Ϣ����"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   435
      Left            =   120
      TabIndex        =   10
      Top             =   3600
      Width           =   3930
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "�Է���Ϣ"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   120
      TabIndex        =   7
      Top             =   240
      Width           =   780
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "�����һ�Է���ַ"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   120
      TabIndex        =   9
      Top             =   3240
      Width           =   1560
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "�ȴ�����"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   3480
      TabIndex        =   8
      Top             =   2760
      Width           =   780
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "���ڴ����뷢������Ϣ"
      BeginProperty Font 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   120
      TabIndex        =   6
      Top             =   1800
      Width           =   1950
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim flag As Boolean

Private Sub a_Connect()
    flag = True
End Sub

Private Sub a_DataArrival(ByVal bytesTotal As Long)
    Dim i As String
    a.GetData i
    Label3.Caption = "���ӳɹ�"
    Comm2.MousePointer = 0
    Form1.MousePointer = 0
    Timer1.Enabled = False
    If i = Chr(0) Then
        Text2.Text = "���ǵ�һ�����뱾�����ҵĿͻ�" + Chr(13) + Chr(10)
    Else
        Text2.Text = Text2.Text + i
    End If
    Text2.SelStart = Len(Text2.Text)
    Send.MousePointer = 0
    Combo1.Enabled = False
    Comm2.Caption = "�Ͽ�����"
    Text1.SetFocus
End Sub
Private Sub a_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, canceldiplay As Boolean)
    flag = False
    Timer1.Enabled = False
    Comm2.MousePointer = 0
    Form1.MousePointer = 0
    MsgBox "��������ʧ��!"
    Label3.Caption = "�ȴ�����"
    Combo1.Enabled = True
    Combo1.SetFocus
    a.Close
    Comm2.Caption = "����"
End Sub

Private Sub Comm1_click()
    a.Close
    Form1.WindowState = 1
    
End Sub

Private Sub Comm2_click()
    If Comm2.Caption = "�Ͽ�����" Then
        a.Close
        Comm2.Caption = "����"
        Label3.Caption = "�ȴ�����"
        Combo1.Enabled = True
        Timer1.Enabled = False
        Comm2.MousePointer = 0
        Form1.MousePointer = 0
    Else
        Text2 = ""
        Label3.Caption = "��������"
        Comm2.MousePointer = 11
        Form1.MousePointer = 11
        Timer1.Enabled = True
        flag = False
        a.Protocol = sckTCPProtocol
        a.RemotePort = 3000
        a.Connect
    End If
End Sub

Private Sub form_dblclick()
    If MsgBox("�رձ�������, ȷ��ô?", 36, "�˳�ϵͳ") = 6 Then
        End
    Else
        Form1.WindowState = 1
    End If
End Sub

Private Sub Form_Load()
    If App.PrevInstance Then
        MsgBox "��ϵͳ�Ѿ�����, �뿴������", 48, "��ʾ"
        'End
    End If
    flag = False
    Load Form2
End Sub

Private Sub send_click()
    Dim s As String
    On Error GoTo ffff
    Send.MousePointer = 11
    If Right(Text1.Text, 1) <> Chr(10) Then
        s = Text1.Text + Chr(13) + Chr(10)
    Else
        s = Text1.Text
    End If
    If flag Then
        a.SendData s
    End If
    Exit Sub
ffff:
    MsgBox "�����ж�", 48, "��ʾ"
    a.Close
    Send.MousePointer = 0
    Comm2.Caption = "����"
    Label3.Caption = "�ȴ�����"
    Combo1.Enabled = True
    Comm2.MousePointer = 0
    Form1.MousePointer = 0
Exit Sub

    
End Sub

Private Sub timer1_timer()
    flag = False
    Timer1.Enabled = False
    Comm2.MousePointer = 0
    Form1.MousePointer = 0
    MsgBox "network connection failure(timeout)!"
    Label3.Caption = "�ȴ�����"
    Combo1.Enabled = True
    Combo1.SetFocus
    a.Close
    Comm2.Caption = "����"
End Sub