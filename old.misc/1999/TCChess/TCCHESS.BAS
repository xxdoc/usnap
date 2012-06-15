Attribute VB_Name = "modTCChess"

Global strGameName As String

Type Point
    X As Integer
    Y As Integer
End Type

' ��ʾ��
    Type NodeExpression
        nArea As Integer
        nNode As Integer
    End Type
    Type ButtonExpression
        nArea As Integer
        nButton As Integer
    End Type

' ����
    Global Const MAXBUTTONCLASS = 64                ' ������������
        ' һ��nPower��nMovementȫ0, nMovement����TWay.nWaste
        Global Const BCS_KERNEL = 1                 ' ������
        Global Const BCS_BOMB = 2                   ' ͬ���ھ�
        Global Const BCS_SPY = 8                    ' ��̽
        Type TButtonClass
            Name As String
            nImportant As Integer                   ' Ȩ��
            nPower As Integer
            nMovement As Integer
            Style As Long
        End Type
    
        Global ButtonClass(MAXBUTTONCLASS) As TButtonClass  ' ��������
        
    Global Const MAXBUTTONS = 128                   ' ĳ������������  + 1
        Type TButton
            bInitialized As Boolean                 ' ��Ϸ��ʼʱ�ѷ�������
            Class As Integer                        ' ��������������, ����TButtonClass[]
            ParkNode As NodeExpression              ' ռ������, ��������ֻ����������ȥ����������
        End Type

' ·��
    Global Const MAXLINKCLASS = 64                  ' ���ͨ��������
        Type TLinkClass
            nWaste As Integer
        End Type
        
        Global TLinkClass(MAXLINKCLASS) As TLinkClass   ' ������·, ������
    
    Global Const MAXNODELINKS = 16                  ' ����������·����
        Type TLink
            nDirection As Integer                   ' ·�߷���
            bOwner As Boolean                       ' ·������, ������
            bValid As Boolean                       ' ��Ч����, Ĭ��TRUE
            DestNode As NodeExpression              ' �������������
            lClass As Integer                       ' ·�����
        End Type

' ���
    Global Const MAXNODES = 256                     ' ���������������
        Global Const NS_DUPLICATABLE = 1            ' �ɵ���פ��
        Global Const NS_PROTECT = 2                 ' ����Ӫ��
        Global Const NS_KILL = 4                    ' ��Ѩ
        Global Const NS_FALLINTO = 8                ' ����ͬ
        'GLOBAL CONST
        Type TNode
        ' ��̬����
            Style As Long                           ' �����
            nHaveLinks As Integer                   ' ������
            Links(MAXNODELINKS) As TLink            ' ������
            Left As Single                          ' ��ֽռλ
            Top As Single
            Width As Single
            Height As Single
        ' ��̬����
            bStayButton As Boolean                  ' ������Ч
            StayButton As ButtonExpression          ' פ������
        End Type

' ��̬����
    Global Const MAXAREAS = 16                  ' ���������        + 1
        Enum SortStyle
            SSFixed = 0
            SSArrangable = 1
            SSRandom = 3
        End Enum
    
        Type TArea
            Name As String
            
            nHaveNodes As Integer           ' ӵ��������
            Nodes(MAXNODES) As TNode        ' �������
            nCurNode As Integer             ' ��ǰ�����
            
            nHaveButtons As Integer         ' ӵ�б�����
            Buttons(MAXBUTTONS) As TButton  ' ��������
            nCurButton As Integer           ' ��ǰ�����
        
            bPlayable As Boolean
            Sortable As SortStyle
            Color As Long                   ' ������ɫ = 0 ��ʾ����
            Points As Integer               ' ӵ�е���
        End Type

    Global nHaveAreas As Integer, Areas(MAXAREAS) As TArea, nCurArea As Integer
    Global nTurningWaste As Integer

' ����ʾ��
Function theNode(ne As NodeExpression) As TNode: theNode = Areas(ne.nArea).Nodes(ne.nNode): End Function
Function ANode(theArea As Integer, theNode As Integer) As NodeExpression: ANode.nArea = theArea: ANode.nNode = theNode: End Function
' ���ӱ�ʾ��
Function theButton(be As ButtonExpression) As TButton: theButton = Areas(be.nArea).Buttons(be.nButton): End Function
Function AButton(theArea As Integer, theButton As Integer) As ButtonExpression: AButton.nArea = theArea: AButton.nButton = theButton: End Function
' ����ʾ����Ч
Function EqualNExp(ne1 As NodeExpression, ne2 As NodeExpression) As Boolean: EqualNExp = (ne1.nArea = ne2.nArea) And (ne1.nNode = ne2.nNode): End Function
' ���ӱ�ʾ����Ч
Function EqualBExp(be1 As ButtonExpression, be2 As ButtonExpression) As Boolean: EqualBExp = (be1.nArea = be2.nArea) And (be1.nButton = be2.nButton): End Function

' �ж������Ƿ����
Function LinkExists(ns As TNode, nDest As NodeExpression) As Boolean
    Dim i As Integer
    For i = 0 To ns.nHaveLinks - 1
        If EqualNExp(ns.Links(i).DestNode, nDest) Then LinkExists = True: Exit Function
    Next
    LinkExists = False
End Function
Function WhereLinkExists(ns As TNode, nDest As NodeExpression) As Integer
    Dim i As Integer
    For i = 0 To ns.nHaveLinks - 1
        If EqualNExp(ns.Links(i).DestNode, nDest) Then WhereLinkExists = i: Exit Function
    Next
    WhereLinkExists = -1
End Function

' ��������
Function AddNodeLink(NExpA As NodeExpression, NExpB As NodeExpression, Optional bDoubleSide As Boolean = True, Optional bAIsOwner As Boolean = True) As Boolean
    Dim bLinkB As Boolean
    Dim nA As TNode, nb As TNode
    nA = theNode(NExpA): nb = theNode(NExpB)
    ' �����Ч��
        AddNodeLink = Not (Not LinkExists(nA, NExpB) And nA.nHaveLinks >= MAXNODELINKS)
        bLinkB = Not (Not LinkExists(nb, NExpA) And nb.nHaveLinks >= MAXNODELINKS)
        AddNodeLink = AddNodeLink And bLinkB
        If Not AddNodeLink Then Exit Function
    ' ��һ����
        If Not LinkExists(nA, NExpB) Then
            nA.nHaveLinks = nA.nHaveLinks + 1
            nA.Links(nA.nHaveLinks - 1).bValid = True
            nA.Links(nA.nHaveLinks - 1).bOwner = bAIsOwner
            nA.Links(nA.nHaveLinks - 1).DestNode = NExpB
        End If
    ' �ڶ�����
        If LinkExists(nb, NExpA) Then
            nb.Links(WhereLinkExists(nb, NExpA)).bOwner = Not bAIsOwner
        Else
            nb.nHaveLinks = nb.nHaveLinks + 1
            nb.Links(nb.nHaveLinks - 1).bValid = bDoubleSide
            nb.Links(nb.nHaveLinks - 1).bOwner = Not bAIsOwner
            nb.Links(nb.nHaveLinks - 1).DestNode = NExpA
        End If
    ' ����
        Areas(NExpA.nArea).Nodes(NExpA.nNode) = nA
        Areas(NExpB.nArea).Nodes(NExpB.nNode) = nb
End Function

' ɾ������
Function DelNodeLink(NExpA As NodeExpression, NExpB As NodeExpression) As Boolean
    Dim nA As TNode, nb As TNode
    Dim i As Integer
    nA = theNode(NExpA): nb = theNode(NExpB)
    ' �����Ч��
        DelNodeLink = LinkExists(nA, NExpB) And LinkExists(nb, NExpA)
    ' ɾ����һ����
        For i = WhereLinkExists(nA, NExpB) + 1 To nA.nHaveLinks - 1
            nA.Links(i - 1) = nA.Links(i)
            nA.nHaveLinks = nA.nHaveLinks - 1
        Next
    ' ɾ���ڶ�����
        For i = WhereLinkExists(nb, NExpA) + 1 To nb.nHaveLinks - 1
            nb.Links(i - 1) = nb.Links(i)
            nb.nHaveLinks = nb.nHaveLinks - 1
        Next
    ' ����
        Areas(NExpA.nArea).Nodes(NExpA.nNode) = nA
        Areas(NExpB.nArea).Nodes(NExpB.nNode) = nb
End Function