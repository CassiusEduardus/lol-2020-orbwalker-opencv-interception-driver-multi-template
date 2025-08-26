# Module Map (heuristic)

## core/main.cpp

**Includes:**
    GetCastWalkSleep.h
    GetClosestEnemy.h
    GetMousePosInRealTime.h
    GetScreenSize.h
    GetSpaceState.h
    GetStatsInRealtime.h


**Detected decls/defs (heuristic):**
    GetClosestEnemy getclosest(screenResolutionID)
    GetStatsInRealtime getstats(screenResolutionID)
    if (MOUSE_STROKE_ENPOS.x > 0)
    int main()
    while (SPACE_STATE_G)
    while (TRUE)


## core/Globais.cpp

**Includes:**
    Estruturas.h


**Detected decls/defs (heuristic):**
    (none)


## core/Estruturas.h

**Includes:**
    interception.h


**Detected decls/defs (heuristic):**
    (none)


## core/GetCastWalkSleep.cpp

**Includes:**
    GetCastWalkSleep.h


**Detected decls/defs (heuristic):**
    if (ATSP_G > 2.50)
    while (1)


## core/GetCastWalkSleep.h

**Includes:**
    (none)


**Detected decls/defs (heuristic):**
    public:
    GetCastWalkSleep()
    void GetCastWalkSleepTimes()


## core/GetScreenSize.cpp

**Includes:**
    GetScreenSize.h


**Detected decls/defs (heuristic):**
    (none)


## core/GetScreenSize.h

**Includes:**
    (none)


**Detected decls/defs (heuristic):**
    inline void GetScreenY()
    int GetScreenResolutionID()
    private:
	inline void GetScreenX()
    public:
	GetScreenSize()


## capture/ScreenCaptureFast.cpp

**Includes:**
    ScreenCaptureFast.h


**Detected decls/defs (heuristic):**
    BitBlt(HDCMemory, 0, 0, screenWidth, screenHeight, HDCScreen, 0, 0, SRCCOPY)
    DeleteDC(HDCMemory)
    DeleteDC(HDCScreen)
    DeleteObject(HBitmap)
    DeleteObject(HOldBitmap)
    HRESULT resultHandle(E_FAIL)
    exit(5)
    if (!currentTextureD3D11)
    if (soma_c > LINESUM && z == 0)
    if (soma_l > LINESUM && y == 0)


## capture/ScreenCaptureFast.h

**Includes:**
    Estruturas.h


**Detected decls/defs (heuristic):**
    bool GetScreenShot()
    bool InitScreenCaptureFastDirectX()
    bool ResizeFrame(ChampPosOffset& posOffset, cv::Mat& inputFrame, cv::Mat& outputFrame)
    public:
    ScreenCaptureFast()
    public:
    ScreenCaptureSlow()
    void GetCurrentFrame(cv::Mat& outputFrame)
    void GetCurrentFrameSlow(cv::Mat& outputFrame)


## vision/GetClosestEnemy.cpp

**Includes:**
    GetClosestEnemy.h


**Detected decls/defs (heuristic):**
    FindEnemyMatch()
    GetCurrentFrame(screenShotFrame)
    GetCurrentFrameSlow(screenShotFrame)
    exit(-1)
    if (SPACE_STATE_G)
    if (detectedEnemys > 0)
    if (distanciaMatchi < distanciaMaxima && distanciaMatchi > 0 && distanciaMatchi <= maxRange)
    if (minConfidence < maxConfidence)
    switch (resolutionID)
    while (TRUE)


## vision/GetClosestEnemy.h

**Includes:**
    ScreenCaptureFast.h


**Detected decls/defs (heuristic):**
    bool FindAllyMatch()
    bool ProcessFrame()
    public:
    GetClosestEnemy(int resolutionID)
    void FindEnemyMatch()
    void GetClosestEnemyPos1366()
    void GetClosestEnemyPos1920()


## vision/GetStatsInRealtime.cpp

**Includes:**
    GetStatsInRealtime.h
    avir.h


**Detected decls/defs (heuristic):**
    BitBlt(HDCMemory, 0, 0, boxWidth, boxHeight, HDCScreen, boxBeginX, boxBeginY, SRCCOPY)
    DeleteDC(HDCMemory)
    DeleteDC(HDCScreen)
    DeleteObject(HBitmap)
    DeleteObject(HOldBitmap)
    ExtractAttackSpeed()
    ExtractLife()
    GetCurrentFrame(startBoxFullInterfaceX, startBoxFullInterfaceY, widthBoxFullInterface, heighBoxFullInterface)
    ResizeAttackSpeedFrame()
    ResizeLifeFrame()
    avir::CImageResizer<> ImageResizer(8)
    exit(-1)
    free(out)
    if (SPACE_STATE_G)
    if (guarda)
    if (j >= 0 && j <= 3)
    if (minConfidence < maxConfidence)
    if (out[i] != ' ')
    if (out[i] != '\0')
    if (out[i] != '\n')
    if (out[i] == '\n' || out[i] == '/')
    switch (resolutionID)
    while (TRUE)


## vision/GetStatsInRealtime.h

**Includes:**
    (none)


**Detected decls/defs (heuristic):**
    bool FindTemplateMatches()
    if (temp > arr[i])
    int FindSmallest(double arr[], int n)
    int FindSmallest(int arr[], int n)
    public:
    GetStatsInRealtime(int resolutionID)
    void ExtractAttackSpeed()
    void ExtractLife()
    void GetCurrentFrame(int boxBeginX, int boxBeginY, int boxWidth, int boxHeight)
    void GetMyChampId()
    void GetMyChampStats()
    void ResizeAttackSpeedFrame()
    void ResizeLifeFrame()


## vision/avir.h

**Includes:**
    (none)


**Detected decls/defs (heuristic):**
    : ItemCount( 0 )
    : Order( -1 )
    :: free( Data )
    :: free( PrevData )
    CBuffer( const CBuffer& Source )
    CBuffer( const capint aCapacity, const int aAlignment = 0 )
    CBuffer< double > Bins( BinCount )
    CBuffer< double > Buf( BufLen )
    CBuffer< double > oscbuf( z2 )
    CBuffer< double > winbuf( z )
    CDSPPeakedCosineLPF p( WFLen2, WFFreq, WFAlpha )
    CDSPPeakedCosineLPF w( Len2, Freq, FltAlpha )
    CDSPWindowGenPeakedCosine wf( Alpha, FilterLength * 0.5 )
    CDSPWindowGenPeakedCosine wf( Alpha, Len2 )
    CDitherer& getDitherer()
    CFilterStep :: applySRGBGamma( ResScanline, NewWidth,
						Vars )
    CImageResizerDithererDefINL< fptype > :: init( aLen, aVars, aTrMul,
			aPkOut )
    CImageResizerVars TmpVars( Vars )
    CRPosBuf& getRPosBuf( const double k, const double o,
			const int FracCount )
    CSineGen f2( Freq2, 0.0 )
    T& add()
    addArray( &fs.Flt[ 0 ], op, l )
    addArray( ip, &fs.PrefixDC[ 0 ], l )
    addBandKernel( Filter, kernbuf1, kernbuf2, y1 - y2,
				x1 * y2 - x2 * y1 )
    addBandKernel( Filter, kernbuf1, kernbuf2, y1 - y2,
				x1 * y2 - y1 )
    addCorrectionFilter( Steps, corrbw, IsPreCorrection, IsModel )
    alloc( Source.Capacity, Source.Alignment )
    allocFilter( fs.Flt, w.FilterLen, true, &FltExt )
    allocFilter( fs.PrefixDC, l, IsModel )
    allocFilter( fs.SuffixDC, fs.FltLatency, IsModel )
    allocinit( NewCapacity, Alignment )
    allocinit( Source.Capacity, Source.Alignment )
    allocinit( aCapacity, aAlignment )
    assignFilterParams( fs, false, DownsampleFactor, FltCutoff,
				DCGain, DoFltAndIntCombo, IsModel )
    assignFilterParams( fs, true, UpsampleFactor, FltCutoff, DCGain,
				DoFltAndIntCombo, IsModel )
    buildFilterSteps( FltSteps, Vars, FltBank, 1.0, UseBuildMode,
				false )
    buildFilterSteps( FltSteps, Vars, FltBank, OutMul, UseBuildMode,
			false )
    buildFilterSteps( TmpSteps, TmpVars, TmpBank, 1.0, m, true )
    buildFilterSteps( TmpSteps, Vars, TmpBank, OutMul, m, true )
    buildSrcTable()
    calcFIRFilterResponse( Flt, FltLen, th, re, im )
    clear()
    const fptype* getFilter( const int i )
    copyArray( &Flt[ i ], &Flt[ 0 ], NewCapacity )
    copyArray( &fs.Flt[ 0 ], op, l )
    copyArray( ip, &fs.PrefixDC[ 0 ], l )
    copyBandKernel( Filter, kernbuf1, kernbuf2, y1 - y2,
			x1 * y2 - x2 * y1 )
    createFilter( i )
    createFilter( i + 1 )
    double generate()
    else
			if( ElCount == 2 )
    else
			if( ElCount == 3 )
    else
			if( ElCount == 4 )
    else
			if( ElCountIO == 2 )
    else
			if( ElCountIO == 3 )
    else
			if( ElCountIO == 4 )
    else
			if( fs.ResampleFactor == 0 )
    else
		if( !UseFltOrig )
    else
		if( ElCount == 2 )
    else
		if( ElCount == 3 )
    else
		if( ElCount == 4 )
    else
		if( ElCountIO == 2 )
    else
		if( ElCountIO == 3 )
    else
		if( ElCountIO == 4 )
    else
		if( NewWidth == 0 || NewHeight == 0 )
    else
		if( ZeroCount == 2 )
    else
		if( ZeroCount == 3 )
    else
		if( k > 0.0 )
    else
	if( Value > maxv )
    else
	if( ipl == 2 )
    else
	if( ipl == 3 )
    else
	if( ipl == 4 )
    extendUpsample( Steps[ upstep ], Steps[ upstep + 1 ])
    fillBandKernel( x1, 1.0, kernbuf1, kernbuf2, oscbuf, winbuf )
    fillBandKernel( x1, x2, kernbuf1, kernbuf2, oscbuf, winbuf )
    fillRPosBuf( fs, Vars )
    fillUsedFracMap( TmpSteps[ TmpVars.ResizeStep ],
					UsedFracMap )
    fillUsedFracMap( TmpSteps[ Vars.ResizeStep ], UsedFracMap )
    freeData()
    getFilter( i )
    if( !IsInFloat )
    if( !IsSrcTableBuilt )
    if( !Steps[ z ].IsUpsample && Steps[ z ].ResampleFactor == 1 )
    if( !UseFltOrig )
    if( !Vars -> UseSRGBGamma )
    if( !fs.IsUpsample && fs.ResampleFactor > 1 )
    if( Buf.k == k && Buf.o == o && Buf.FracCount == FracCount )
    if( Capacity > 0 )
    if( DoDataCopy )
    if( DoFltAndIntCombo )
    if( DoHBFltAdd )
    if( DownsampleFactor < 1 )
    if( DownsampleFactor > 16 )
    if( ElCount == 1 )
    if( ElCountIO == 1 )
    if( FltBank == FixedFilterBank )
    if( FltCutoff == 0.0 )
    if( FltExt != NULL )
    if( ForceHiOrder || IntBitDepth > 8 )
    if( FracCount < 2 )
    if( FracUseMap[ i ] != 0 )
    if( IsInFloat )
    if( IsInitRequired )
    if( IsLogBands )
    if( IsModel )
    if( IsOutFloat )
    if( IsUpsample )
    if( IsUpsample || InPrefix + InSuffix == 0 )
    if( NewCapacity < Capacity )
    if( NewCapacity >= Capacity )
    if( NewCount > ItemCount )
    if( NewHeight > SrcHeight )
    if( NewWidth > SrcWidth )
    if( Order > 0 )
    if( OutMul != 1.0 )
    if( PrevCapacity > 0 )
    if( ReqCapacity <= Capacity )
    if( ReqOrder == Order && NewWFLen2 == WFLen2 && NewWFFreq == WFFreq &&
			NewWFAlpha == WFAlpha && ReqFracCount == FracCount &&
			aExtFilter == ExtFilter )
    if( SrcScanlineSize < 1 )
    if( SrcWidth == 0 || SrcHeight == 0 )
    if( TableFillFlags[ k ] != 0 )
    if( Thresh > BinCount )
    if( TrMul0 == 1.0 )
    if( UpsampleFactor > 1 )
    if( UseBuildMode == PrevUseBuildMode && ky == kx )
    if( UseFirstVirtBand )
    if( UseFltOrig )
    if( UseLastVirtBand )
    if( Vars -> UseSRGBGamma )
    if( Vars.BuildMode >= 0 )
    if( Vars.UseSRGBGamma )
    if( Vars.k <= 1.0 )
    if( Vars.packmode != 0 )
    if( Vars.packmode == 0 )
    if( ZeroCount == 1 )
    if( aAlignment == 0 )
    if( bw <= 1.0 )
    if( c < BestScore )
    if( fltlat == 0 )
    if( fs.InPrefix > MaxPrefix[ ib ])
    if( fs.IsUpsample )
    if( fs.OutBuf == 2 )
    if( fs.OutElIncr > fs2.InElIncr )
    if( fs.OutLen > MaxLen[ ob ])
    if( fs.OutLen > PrevLen )
    if( fs.OutPrefix > MaxPrefix[ ob ])
    if( fs.ResampleFactor != 0 )
    if( fs.ResampleFactor == 0 )
    if( i > 0 )
    if( k == 0.0 )
    if( k > 1.0 )
    if( l < 0 )
    if( l <= 0 )
    if( l > MaxLen[ ib ])
    if( l > MaxLen[ ob ])
    if( l > l0 )
    if( r > SrcFilterLen )
    if( upstep != -1 )
    if( x1 < 1.0 )
    increaseCapacity( NewCapacity )
    initOscBuf( oscbuf )
    initWinBuf( winbuf, WFAlpha )
    modifyCorrFilterDCGain( FltSteps, 1.0 / OutMul )
    optimizeFIRFilter( Filter, fs.FltLatency )
    optimizeFIRFilter( fs.FltOrig, fs.FltLatency )
    printf( "***\n" )
    processScanlineQueue()
    public:
		virtual void process()
    public:
	CImageResizerThreadPool()
    replicateArray( Src, ElCount, Src + ElCount, InSuffix, ElCount )
    replicateArray( Src, ElCount, Src - ElCount, InPrefix, -ElCount )
    return( *Items[ Index ])
    return( *this )
    return( 1 )
    return( Buf )
    return( Capacity )
    return( DataAligned )
    return( Ditherer )
    return( FilterLen )
    return( FracCount )
    return( ItemCount )
    return( Len2 == b2.Len2 && Freq == b2.Freq && Alpha == b2.Alpha &&
			DCGain == b2.DCGain )
    return( NewBuf )
    return( Order )
    return( Order == s.Order && WFLen2 == s.WFLen2 &&
			WFFreq == s.WFFreq && WFAlpha == s.WFAlpha &&
			FracCount == s.FracCount && ExtFilter == s.ExtFilter )
    return( Res )
    return( Value )
    return( false )
    return( ic )
    return( l * 2 - 1 )
    return( maxv )
    return( minv )
    return( res )
    return( s + s2 / ScanlineCount )
    return( true )
    return( z - 1 )
    return( z2 - 1 )
    static bool isRecursive()
    static int calcComplexity( const CFilterSteps& Steps,
		const CImageResizerVars& Vars, const CBuffer< uint8_t >& UsedFracMap,
		const int ScanlineCount )
    static int calcFilterLength( const double aFilterLength, int& Latency )
    static void addSharpenTest( CFilterSteps& Steps, const double bw,
		const bool IsModel )
    static void allocFilter( CBuffer< fptype >& Flt, const int ReqCapacity,
		const bool IsModel = false, int* const FltExt = NULL )
    static void applySRGBGamma( fptype* p, int l,
		const CImageResizerVars& Vars0 )
    static void extendUpsample( CFilterStep& fs, CFilterStep& NextStep )
    static void fillRPosBuf( CFilterStep& fs, const CImageResizerVars& Vars )
    static void fillUsedFracMap( const CFilterStep& fs,
		CBuffer< uint8_t >& UsedFracMap )
    static void updateBufLenAndRPosPtrs( CFilterSteps& Steps,
		CImageResizerVars& Vars, const int ResElIncr )
    static void updateFilterStepBuffers( CFilterSteps& Steps,
		CImageResizerVars& Vars,
		typename CFilterStep :: CRPosBufArray& RPosBufArray, int SrcLen,
		const int NewLen )
    switch( ScanlineOp )
    template< class T >
	void generateLPF( T* op, const double DCGain )
    template< class T >
inline T clamp( const T& Value, const T minv, const T maxv )
    template< class T >
inline T convertLin2SRGB( const T s )
    template< class T >
inline T convertSRGB2Lin( const T s )
    template< class T >
inline T pow24_sRGB( const T x )
    template< class T >
inline T pow24i_sRGB( const T x )
    template< class T >
inline T round( const T d )
    template< class T >
inline void calcFIRFilterResponse( const T* flt, int fltlen,
	const double th, double& re0, double& im0, const int fltlat = 0 )
    template< class T >
inline void normalizeFIRFilter( T* const p, const int l, const double DCGain,
	const int pstep = 1 )
    template< class T1, class T2 >
inline void addArray( const T1* ip, T2* op, int l,
	const int ipinc = 1, const int opinc = 1 )
    template< class T1, class T2 >
inline void copyArray( const T1* ip, T2* op, int l,
	const int ipinc = 1, const int opinc = 1 )
    template< class T1, class T2 >
inline void replicateArray( const T1* const ip, const int ipl, T2* op, int l,
	const int opinc )
    template< class Tout >
	static void unpackScanline( const fptype* ip, Tout* op, int l,
		const CImageResizerVars& Vars0 )
    template< class Tp >
	inline Tp alignptr( const Tp ptr, const uintptr_t align )
    updateBufLenAndRPosPtrs( FltSteps, Vars, NewWidth )
    updateFilterStepBuffers( FltSteps, Vars, RPosBufArray, SrcHeight,
			NewHeight )
    updateFilterStepBuffers( FltSteps, Vars, RPosBufArray, SrcWidth,
			NewWidth )
    updateFilterStepBuffers( TmpSteps, TmpVars, RPosBufArray,
					SrcHeight, NewHeight )
    updateFilterStepBuffers( TmpSteps, Vars, RPosBufArray,
					SrcWidth, NewWidth )
    virtual void addWorkload( CWorkload* const Workload )
    virtual void removeAllWorkloads()
    virtual void startAllWorkloads()
    virtual void waitAllWorkloadsToFinish()
    void addScanlineToQueue( void* const SrcBuf, void* const ResBuf )
    void alloc( const capint aCapacity, const int aAlignment = 0 )
    void allocinit( const capint aCapacity, const int aAlignment )
    void buildFilter( const double* const BandGains, double* const Filter )
    void buildSrcTable()
    void clear()
    void copyInitParams( const CDSPFracFilterBankLin& s )
    void createAllFilters()
    void createFilter( const int k )
    void dither( fptype* const ResScanline )
    void fillBandKernel( const double x1, const double x2, double* kernbuf1,
		double* kernbuf2, double* oscbuf, const double* const winbuf )
    void forceCapacity( const capint NewCapacity )
    void free()
    void freeData()
    void increaseCapacity( const capint NewCapacity,
		const bool DoDataCopy = true )
    void init( const double SampleRate, const double aFilterLength,
		const int aBandCount, const double MinFreq, const double MaxFreq,
		const bool IsLogBands, const double WFAlpha )
    void init( const int ReqFracCount, const int ReqOrder,
		const double BaseLen, const double Cutoff, const double aWFAlpha,
		const CFltBuffer& aExtFilter, const int aAlignment = 0,
		const int FltLenAlign = 1 )
    void init( const int aLen, const CImageResizerVars& aVars,
		const double aTrMul, const double aPkOut )
    void init( const int aThreadIndex, const int aThreadCount,
			const CFilterSteps& aSteps, const CImageResizerVars& aVars )
    void initScanlineQueue( const EScanlineOperation aOp,
			const int TotalLines, const int aSrcLen, const int aSrcIncr = 0,
			const int aResIncr = 0 )
    void processScanlineQueue()
    void resizeScanlineH( const Tin* const SrcBuf, fptype* const ResBuf )
    void resizeScanlineV( const fptype* const SrcBuf,
			fptype* const ResBuf )
    void setItemCount( const int NewCount )
    void truncateCapacity( const capint NewCapacity )
    void updateCapacity( const capint ReqCapacity )
    while( Ext > 0 )
    while( ItemCount < NewCount )
    while( ItemCount > 0 )
    while( ItemCount > NewCount )
    while( NewCapacity < ReqCapacity )
    while( fltlen > 0 )
    while( i > 0 )
    while( j < LenE )
    while( l > 0 )
    while( l >= 0 )
    while( t <= fl2 )
    while( t > 0 )
    while( true )


## input/GetMousePosInRealTime.cpp

**Includes:**
    GetMousePosInRealTime.h


**Detected decls/defs (heuristic):**
    interception_send(MOUSE_CONTEXT_G.Contexto_Mouse, MOUSE_CONTEXT_G.DeviceID_Mouse, &MOUSE_CONTEXT_G.Stroke_Mo_Mouse, 1)
    interception_set_filter(MOUSE_CONTEXT_G.Contexto_Mouse, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_MOVE)
    point position(screenWidth / 2, screenHeight / 2)


## input/GetMousePosInRealTime.h

**Includes:**
    Estruturas.h


**Detected decls/defs (heuristic):**
    public:
    GetMousePosInRealTime()
    void GetMousePos()


## input/GetSpaceState.cpp

**Includes:**
    Estruturas.h
    GetSpaceState.h


**Detected decls/defs (heuristic):**
    if (KBD_Context.Keystrok_Teclado.code != SCANCODE_SPACE)
    if (KBD_Context.Keystrok_Teclado.code == SCANCODE_SPACE && KBD_Context.Keystrok_Teclado.state == INTERCEPTION_KEY_DOWN)
    if (KBD_Context.Keystrok_Teclado.code == SCANCODE_SPACE && KBD_Context.Keystrok_Teclado.state == INTERCEPTION_KEY_UP)
    interception_destroy_context(KBD_Context.Contexto_Teclado)
    interception_set_filter(KBD_Context.Contexto_Teclado, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP)


## input/GetSpaceState.h

**Includes:**
    (none)


**Detected decls/defs (heuristic):**
    public:
    GetSpaceState()
    void GetSpaceST()


## input/interception.c

**Includes:**
    interception.h


**Detected decls/defs (heuristic):**
    CloseHandle(device_array[i].handle)
    CloseHandle(device_array[i].unempty)
    DeviceIoControl(device_array[device - 1].handle, IOCTL_GET_HARDWARE_ID, NULL, 0, hardware_id_buffer, buffer_size, &output_size, NULL)
    InterceptionContext interception_create_context(void)
    InterceptionDevice interception_wait(InterceptionContext context)
    InterceptionDevice interception_wait_with_timeout(InterceptionContext context, unsigned long milliseconds)
    InterceptionFilter interception_get_filter(InterceptionContext context, InterceptionDevice device)
    InterceptionPrecedence interception_get_precedence(InterceptionContext context, InterceptionDevice device)
    if (device_array[i].handle == INVALID_HANDLE_VALUE)
    if(device_array[i].unempty == NULL)
    int interception_is_invalid(InterceptionDevice device)
    int interception_is_keyboard(InterceptionDevice device)
    int interception_is_mouse(InterceptionDevice device)
    int interception_receive(InterceptionContext context, InterceptionDevice device, InterceptionStroke *stroke, unsigned int nstroke)
    int interception_send(InterceptionContext context, InterceptionDevice device, const InterceptionStroke *stroke, unsigned int nstroke)
    interception_destroy_context(device_array)
    return interception_wait_with_timeout(context, INFINITE)
    unsigned int interception_get_hardware_id(InterceptionContext context, InterceptionDevice device, void *hardware_id_buffer, unsigned int buffer_size)
    void interception_destroy_context(InterceptionContext context)
    void interception_set_filter(InterceptionContext context, InterceptionPredicate interception_predicate, InterceptionFilter filter)
    void interception_set_precedence(InterceptionContext context, InterceptionDevice device, InterceptionPrecedence precedence)


## input/interception.h

**Includes:**
    (none)


**Detected decls/defs (heuristic):**
    InterceptionContext INTERCEPTION_API interception_create_context(void)
    InterceptionDevice INTERCEPTION_API interception_wait(InterceptionContext context)
    InterceptionDevice INTERCEPTION_API interception_wait_with_timeout(InterceptionContext context, unsigned long milliseconds)
    InterceptionFilter INTERCEPTION_API interception_get_filter(InterceptionContext context, InterceptionDevice device)
    InterceptionPrecedence INTERCEPTION_API interception_get_precedence(InterceptionContext context, InterceptionDevice device)
    int INTERCEPTION_API interception_is_invalid(InterceptionDevice device)
    int INTERCEPTION_API interception_is_keyboard(InterceptionDevice device)
    int INTERCEPTION_API interception_is_mouse(InterceptionDevice device)
    int INTERCEPTION_API interception_receive(InterceptionContext context, InterceptionDevice device, InterceptionStroke *stroke, unsigned int nstroke)
    int INTERCEPTION_API interception_send(InterceptionContext context, InterceptionDevice device, const InterceptionStroke *stroke, unsigned int nstroke)
    unsigned int INTERCEPTION_API interception_get_hardware_id(InterceptionContext context, InterceptionDevice device, void *hardware_id_buffer, unsigned int buffer_size)
    void INTERCEPTION_API interception_destroy_context(InterceptionContext context)
    void INTERCEPTION_API interception_set_filter(InterceptionContext context, InterceptionPredicate predicate, InterceptionFilter filter)
    void INTERCEPTION_API interception_set_precedence(InterceptionContext context, InterceptionDevice device, InterceptionPrecedence precedence)

