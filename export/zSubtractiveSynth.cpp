/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_67 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_64 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_67;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_64()
            {
            }
            
            ~RNBOSubpatcher_64()
            {
            }
            
            virtual RNBOSubpatcher_67* getPatcher() const {
                return static_cast<RNBOSubpatcher_67 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number safediv(number num, number denom) {
                return (denom == 0.0 ? 0.0 : num / denom);
            }
            
            number maximum(number x, number y) {
                return (x < y ? y : x);
            }
            
            number mstosamps(MillisecondTime ms) {
                return ms * this->sr * 0.001;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
            
                this->gen_01_perform(
                    in2,
                    in2,
                    this->gen_01_in3,
                    this->gen_01_in4,
                    this->gen_01_in5,
                    this->gen_01_in6,
                    this->gen_01_attack_lockout,
                    this->signals[0],
                    n
                );
            
                this->dspexpr_01_perform(in1, this->signals[0], out1, n);
                this->signalforwarder_01_perform(this->signals[0], out2, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 1; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->gen_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_01_getPresetValue(getSubState(preset, "attack"));
                this->param_02_getPresetValue(getSubState(preset, "decay"));
                this->param_03_getPresetValue(getSubState(preset, "sustain"));
                this->param_04_getPresetValue(getSubState(preset, "release"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_01_value_set(v);
                    break;
                    }
                case 1:
                    {
                    this->param_02_value_set(v);
                    break;
                    }
                case 2:
                    {
                    this->param_03_value_set(v);
                    break;
                    }
                case 3:
                    {
                    this->param_04_value_set(v);
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_01_value;
                    }
                case 1:
                    {
                    return this->param_02_value;
                    }
                case 2:
                    {
                    return this->param_03_value;
                    }
                case 3:
                    {
                    return this->param_04_value;
                    }
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 4;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "attack";
                    }
                case 1:
                    {
                    return "decay";
                    }
                case 2:
                    {
                    return "sustain";
                    }
                case 3:
                    {
                    return "release";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "poly/env.adsr/attack";
                    }
                case 1:
                    {
                    return "poly/env.adsr/decay";
                    }
                case 2:
                    {
                    return "poly/env.adsr/sustain";
                    }
                case 3:
                    {
                    return "poly/env.adsr/release";
                    }
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 30;
                        info->min = 0;
                        info->max = 5000;
                        info->exponent = 3;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 1:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 200;
                        info->min = 1;
                        info->max = 5000;
                        info->exponent = 3;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 2:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0.5;
                        info->min = 0;
                        info->max = 1;
                        info->exponent = 0.8;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 3:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 300;
                        info->min = 1;
                        info->max = 90000;
                        info->exponent = 5;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 2:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        ParameterValue normalizedValue = (value - 0) / (1 - 0);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(
                                    rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)0.8
                                );
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                case 0:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 5000 ? 5000 : value));
                        ParameterValue normalizedValue = (value - 0) / (5000 - 0);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(
                                    rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)3
                                );
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                case 1:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 5000 ? 5000 : value));
                        ParameterValue normalizedValue = (value - 1) / (5000 - 1);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(
                                    rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)3
                                );
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                case 3:
                    {
                    {
                        value = (value < 1 ? 1 : (value > 90000 ? 90000 : value));
                        ParameterValue normalizedValue = (value - 1) / (90000 - 1);
            
                        {
                            if (normalizedValue != 0.0) {
                                normalizedValue = rnbo_exp(
                                    rnbo_log((normalizedValue <= 0.0000000001 ? 0.0000000001 : normalizedValue)) * 1. / (number)5
                                );
                            }
                        }
            
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 2:
                    {
                    {
                        {
                            if (value == 0.0) {
                                return 0;
                            } else {
                                return 0 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 0.8) * (1 - 0);
                            }
                        }
                    }
                    }
                case 0:
                    {
                    {
                        {
                            if (value == 0.0) {
                                return 0;
                            } else {
                                return 0 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 3) * (5000 - 0);
                            }
                        }
                    }
                    }
                case 1:
                    {
                    {
                        {
                            if (value == 0.0) {
                                return 1;
                            } else {
                                return 1 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 3) * (5000 - 1);
                            }
                        }
                    }
                    }
                case 3:
                    {
                    {
                        {
                            if (value == 0.0) {
                                return 1;
                            } else {
                                return 1 + rnbo_exp(rnbo_log((value <= 0.0000000001 ? 0.0000000001 : value)) * 5) * (90000 - 1);
                            }
                        }
                    }
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_01_value_constrain(value);
                    }
                case 1:
                    {
                    return this->param_02_value_constrain(value);
                    }
                case 2:
                    {
                    return this->param_03_value_constrain(value);
                    }
                case 3:
                    {
                    return this->param_04_value_constrain(value);
                    }
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void param_01_value_set(number v) {
                v = this->param_01_value_constrain(v);
                this->param_01_value = v;
                this->sendParameter(0, false);
            
                if (this->param_01_value != this->param_01_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_01_lastValue = this->param_01_value;
                }
            
                this->gen_01_in3_set(v);
            }
            
            void param_02_value_set(number v) {
                v = this->param_02_value_constrain(v);
                this->param_02_value = v;
                this->sendParameter(1, false);
            
                if (this->param_02_value != this->param_02_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_02_lastValue = this->param_02_value;
                }
            
                this->gen_01_in4_set(v);
            }
            
            void param_03_value_set(number v) {
                v = this->param_03_value_constrain(v);
                this->param_03_value = v;
                this->sendParameter(2, false);
            
                if (this->param_03_value != this->param_03_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_03_lastValue = this->param_03_value;
                }
            
                this->gen_01_in5_set(v);
            }
            
            void param_04_value_set(number v) {
                v = this->param_04_value_constrain(v);
                this->param_04_value = v;
                this->sendParameter(3, false);
            
                if (this->param_04_value != this->param_04_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_04_lastValue = this->param_04_value;
                }
            
                this->gen_01_in6_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 2;
            }
            
            Index getNumOutputChannels() const {
                return 2;
            }
            
            void initializeObjects() {
                this->gen_01_attack_has_ended_init();
                this->gen_01_sustain_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
            
                {
                    this->scheduleParamInit(0, 0);
                }
            
                {
                    this->scheduleParamInit(1, 0);
                }
            
                {
                    this->scheduleParamInit(2, 0);
                }
            
                {
                    this->scheduleParamInit(3, 0);
                }
            }
            
            void allocateDataRefs() {}
            
            number param_01_value_constrain(number v) const {
                v = (v > 5000 ? 5000 : (v < 0 ? 0 : v));
                return v;
            }
            
            void gen_01_in3_set(number v) {
                this->gen_01_in3 = v;
            }
            
            number param_02_value_constrain(number v) const {
                v = (v > 5000 ? 5000 : (v < 1 ? 1 : v));
                return v;
            }
            
            void gen_01_in4_set(number v) {
                this->gen_01_in4 = v;
            }
            
            number param_03_value_constrain(number v) const {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void gen_01_in5_set(number v) {
                this->gen_01_in5 = v;
            }
            
            number param_04_value_constrain(number v) const {
                v = (v > 90000 ? 90000 : (v < 1 ? 1 : v));
                return v;
            }
            
            void gen_01_in6_set(number v) {
                this->gen_01_in6 = v;
            }
            
            void gen_01_perform(
                const Sample * in1,
                const Sample * in2,
                number in3,
                number in4,
                number in5,
                number in6,
                number attack_lockout,
                SampleValue * out1,
                Index n
            ) {
                RNBO_UNUSED(attack_lockout);
                auto __gen_01_sustain_value = this->gen_01_sustain_value;
                auto __gen_01_attack_has_ended_value = this->gen_01_attack_has_ended_value;
                auto min_1_0 = this->maximum(in3, 0.1);
                auto min_2_1 = this->maximum(in4, 0.1);
                number clamp_3_2 = (in5 > 1 ? 1 : (in5 < 0 ? 0 : in5));
                auto min_4_3 = this->maximum(in6, 0.1);
                number attack_iter_interval_8 = this->mstosamps(min_1_0) * 0.33333333333333;
                number release_iter_interval_9 = this->mstosamps(min_4_3) * 0.33333333333333;
                number decay_iter_interval_10 = this->mstosamps(min_2_1) * 0.33333333333333;
                number sustain_smoothing_12 = 1 - ((this->mstosamps(20) == 0. ? 0. : (number)1 / this->mstosamps(20)));
                Index i;
            
                for (i = 0; i < n; i++) {
                    number trigger_5 = this->gen_01_delta_4_next(in2[(Index)i] > 0) > 0;
                    number is_released_6 = in1[(Index)i] == 0;
                    number is_attacking_7 = ((bool)(trigger_5) || (bool)(!(bool)(__gen_01_attack_has_ended_value))) && ((bool)(!(bool)(is_released_6)) || 0);
                    number decay_iter_interval_5_11 = !(bool)(is_released_6) * decay_iter_interval_10 + is_released_6 * release_iter_interval_9;
                    __gen_01_sustain_value = clamp_3_2 + sustain_smoothing_12 * (__gen_01_sustain_value - clamp_3_2);
                    number ad_target_13 = (is_attacking_7 > 0 ? 1.0523956964913 : -0.052395696491256);
                    number asr_target_14 = ((bool)(!(bool)(is_released_6)) || (bool)(is_attacking_7) ? 1.0523956964913 : -0.052395696491256);
                    number ad_16 = this->gen_01_slide_15_next(ad_target_13, attack_iter_interval_8, decay_iter_interval_5_11);
                    number ad_6_17 = (ad_16 > 1 ? 1 : (ad_16 < 0 ? 0 : ad_16));
                    number asr_19 = this->gen_01_slide_18_next(asr_target_14, attack_iter_interval_8, release_iter_interval_9);
                    number asr_7_20 = (asr_19 > 1 ? 1 : (asr_19 < 0 ? 0 : asr_19));
                    __gen_01_attack_has_ended_value = (bool)(!(bool)(is_attacking_7)) || ad_6_17 >= 1;
                    number expr_8_21 = ad_6_17 + __gen_01_sustain_value * (asr_7_20 - ad_6_17);
                    out1[(Index)i] = expr_8_21;
                }
            
                this->gen_01_attack_has_ended_value = __gen_01_attack_has_ended_value;
                this->gen_01_sustain_value = __gen_01_sustain_value;
            }
            
            void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
                for (Index i = 0; i < n; i++) {
                    output[(Index)i] = input[(Index)i];
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number gen_01_attack_has_ended_getvalue() {
                return this->gen_01_attack_has_ended_value;
            }
            
            void gen_01_attack_has_ended_setvalue(number val) {
                this->gen_01_attack_has_ended_value = val;
            }
            
            void gen_01_attack_has_ended_reset() {
                this->gen_01_attack_has_ended_value = 0;
            }
            
            void gen_01_attack_has_ended_init() {
                this->gen_01_attack_has_ended_value = 0;
            }
            
            number gen_01_sustain_getvalue() {
                return this->gen_01_sustain_value;
            }
            
            void gen_01_sustain_setvalue(number val) {
                this->gen_01_sustain_value = val;
            }
            
            void gen_01_sustain_reset() {
                this->gen_01_sustain_value = 0;
            }
            
            void gen_01_sustain_init() {
                this->gen_01_sustain_value = 0.5;
            }
            
            number gen_01_delta_4_next(number x) {
                number temp = (number)(x - this->gen_01_delta_4_prev);
                this->gen_01_delta_4_prev = x;
                return temp;
            }
            
            void gen_01_delta_4_dspsetup() {
                this->gen_01_delta_4_reset();
            }
            
            void gen_01_delta_4_reset() {
                this->gen_01_delta_4_prev = 0;
            }
            
            number gen_01_slide_15_next(number x, number up, number down) {
                number temp = x - this->gen_01_slide_15_prev;
                auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
                auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
                this->gen_01_slide_15_prev = this->gen_01_slide_15_prev + ((x > this->gen_01_slide_15_prev ? iup : idown)) * temp;
                return this->gen_01_slide_15_prev;
            }
            
            void gen_01_slide_15_reset() {
                this->gen_01_slide_15_prev = 0;
            }
            
            number gen_01_slide_18_next(number x, number up, number down) {
                number temp = x - this->gen_01_slide_18_prev;
                auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
                auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
                this->gen_01_slide_18_prev = this->gen_01_slide_18_prev + ((x > this->gen_01_slide_18_prev ? iup : idown)) * temp;
                return this->gen_01_slide_18_prev;
            }
            
            void gen_01_slide_18_reset() {
                this->gen_01_slide_18_prev = 0;
            }
            
            void gen_01_dspsetup(bool force) {
                if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->gen_01_setupDone = true;
                this->gen_01_delta_4_dspsetup();
            }
            
            void param_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_01_value;
            }
            
            void param_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_01_value_set(preset["value"]);
            }
            
            void param_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_02_value;
            }
            
            void param_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_02_value_set(preset["value"]);
            }
            
            void param_03_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_03_value;
            }
            
            void param_03_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_03_value_set(preset["value"]);
            }
            
            void param_04_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_04_value;
            }
            
            void param_04_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_04_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                dspexpr_01_in1 = 0;
                dspexpr_01_in2 = 0;
                gen_01_in1 = 0;
                gen_01_in2 = 0;
                gen_01_in3 = 0;
                gen_01_in4 = 0;
                gen_01_in5 = 0;
                gen_01_in6 = 0;
                gen_01_attack_lockout = 0;
                param_01_value = 30;
                param_02_value = 200;
                param_03_value = 0.5;
                param_04_value = 300;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                gen_01_attack_has_ended_value = 0;
                gen_01_sustain_value = 0;
                gen_01_delta_4_prev = 0;
                gen_01_slide_15_prev = 0;
                gen_01_slide_18_prev = 0;
                gen_01_setupDone = false;
                param_01_lastValue = 0;
                param_02_lastValue = 0;
                param_03_lastValue = 0;
                param_04_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_01_in1;
                number dspexpr_01_in2;
                number gen_01_in1;
                number gen_01_in2;
                number gen_01_in3;
                number gen_01_in4;
                number gen_01_in5;
                number gen_01_in6;
                number gen_01_attack_lockout;
                number param_01_value;
                number param_02_value;
                number param_03_value;
                number param_04_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[1];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number gen_01_attack_has_ended_value;
                number gen_01_sustain_value;
                number gen_01_delta_4_prev;
                number gen_01_slide_15_prev;
                number gen_01_slide_18_prev;
                bool gen_01_setupDone;
                number param_01_lastValue;
                number param_02_lastValue;
                number param_03_lastValue;
                number param_04_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_65 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_67;
            friend class rnbomatic;
            
            public:
            
            class RNBOSubpatcher_57 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_65;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_57()
                        {
                        }
                        
                        ~RNBOSubpatcher_57()
                        {
                        }
                        
                        virtual RNBOSubpatcher_65* getPatcher() const {
                            return static_cast<RNBOSubpatcher_65 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                        }
                        
                        inline number safesqrt(number num) {
                            return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
                        }
                        
                        Index vectorsize() const {
                            return this->vs;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                            const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                            const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                            const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
                        
                            this->filtercoeff_01_perform(
                                in2,
                                this->filtercoeff_01_gain,
                                in3,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                n
                            );
                        
                            this->biquad_tilde_01_perform(
                                in1,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                out1,
                                n
                            );
                        
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 5; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            this->filtercoeff_01_dspsetup(forceDSPSetup);
                            this->biquad_tilde_01_dspsetup(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& ) {}
                        
                        void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 0;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
                        
                        void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                        
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                        }
                        
                        protected:
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 3;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 1;
                        }
                        
                        void initializeObjects() {}
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {}
                        
                        void allocateDataRefs() {}
                        
                        void filtercoeff_01_perform(
                            const Sample * frequency,
                            number gain,
                            const Sample * q,
                            SampleValue * a0,
                            SampleValue * a1,
                            SampleValue * a2,
                            SampleValue * b1,
                            SampleValue * b2,
                            Index n
                        ) {
                            RNBO_UNUSED(gain);
                            auto __filtercoeff_01_activeResamp = this->filtercoeff_01_activeResamp;
                            auto __filtercoeff_01_resamp_counter = this->filtercoeff_01_resamp_counter;
                            auto __filtercoeff_01_K_EPSILON = this->filtercoeff_01_K_EPSILON;
                        
                            for (Index i = 0; i < n; i++) {
                                number local_q = q[(Index)i];
                                number local_gain = 1;
                        
                                if (local_gain < 0)
                                    local_gain = 0;
                        
                                number local_frequency = frequency[(Index)i];
                        
                                if (local_q < __filtercoeff_01_K_EPSILON)
                                    local_q = __filtercoeff_01_K_EPSILON;
                        
                                local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
                                __filtercoeff_01_resamp_counter--;
                        
                                if (__filtercoeff_01_resamp_counter <= 0) {
                                    __filtercoeff_01_resamp_counter = __filtercoeff_01_activeResamp;
                                    this->filtercoeff_01_updateTerms(local_frequency, local_gain, local_q);
                                }
                        
                                a0[(Index)i] = this->filtercoeff_01_la0;
                                a1[(Index)i] = this->filtercoeff_01_la1;
                                a2[(Index)i] = this->filtercoeff_01_la2;
                                b1[(Index)i] = this->filtercoeff_01_lb1;
                                b2[(Index)i] = this->filtercoeff_01_lb2;
                            }
                        
                            this->filtercoeff_01_resamp_counter = __filtercoeff_01_resamp_counter;
                        }
                        
                        void biquad_tilde_01_perform(
                            const Sample * x,
                            const Sample * a0,
                            const Sample * a1,
                            const Sample * a2,
                            const Sample * b1,
                            const Sample * b2,
                            SampleValue * out1,
                            Index n
                        ) {
                            auto __biquad_tilde_01_y2 = this->biquad_tilde_01_y2;
                            auto __biquad_tilde_01_y1 = this->biquad_tilde_01_y1;
                            auto __biquad_tilde_01_x2 = this->biquad_tilde_01_x2;
                            auto __biquad_tilde_01_x1 = this->biquad_tilde_01_x1;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_01_x1 * a1[(Index)i] + __biquad_tilde_01_x2 * a2[(Index)i] - (__biquad_tilde_01_y1 * b1[(Index)i] + __biquad_tilde_01_y2 * b2[(Index)i]);
                                __biquad_tilde_01_x2 = __biquad_tilde_01_x1;
                                __biquad_tilde_01_x1 = x[(Index)i];
                                __biquad_tilde_01_y2 = __biquad_tilde_01_y1;
                                __biquad_tilde_01_y1 = tmp;
                                out1[(Index)i] = tmp;
                            }
                        
                            this->biquad_tilde_01_x1 = __biquad_tilde_01_x1;
                            this->biquad_tilde_01_x2 = __biquad_tilde_01_x2;
                            this->biquad_tilde_01_y1 = __biquad_tilde_01_y1;
                            this->biquad_tilde_01_y2 = __biquad_tilde_01_y2;
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void biquad_tilde_01_reset() {
                            this->biquad_tilde_01_x1 = 0;
                            this->biquad_tilde_01_x2 = 0;
                            this->biquad_tilde_01_y1 = 0;
                            this->biquad_tilde_01_y2 = 0;
                        }
                        
                        void biquad_tilde_01_dspsetup(bool force) {
                            if ((bool)(this->biquad_tilde_01_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->biquad_tilde_01_reset();
                            this->biquad_tilde_01_setupDone = true;
                        }
                        
                        array<number, 5> filtercoeff_01_localop_next(number frequency, number q, number gain, number type) {
                            number omega = frequency * this->filtercoeff_01_localop_twopi_over_sr;
                            this->filtercoeff_01_localop_cs = rnbo_cos(omega);
                            this->filtercoeff_01_localop_sn = rnbo_sin(omega);
                            this->filtercoeff_01_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
                            this->filtercoeff_01_localop_one_over_q = (number)1 / q;
                            this->filtercoeff_01_localop_alpha = this->filtercoeff_01_localop_sn * 0.5 * this->filtercoeff_01_localop_one_over_q;
                        
                            switch ((int)type) {
                            case 5:
                                {
                                this->filtercoeff_01_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_01_localop_beta = this->safesqrt(
                                    (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
                                );
                        
                                this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_01_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_01_localop_beta = this->safesqrt(
                                    (this->filtercoeff_01_localop_A * this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_one_over_q - (this->filtercoeff_01_localop_A - 1.) * (this->filtercoeff_01_localop_A - 1.)
                                );
                        
                                this->filtercoeff_01_localop_b0 = (number)1 / (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn);
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_01_localop_A = this->safesqrt(gain);
                                this->filtercoeff_01_localop_one_over_a = (this->filtercoeff_01_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_01_localop_A);
                                this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a);
                                break;
                                }
                            case 9:
                            case 10:
                            case 11:
                            case 13:
                            case 14:
                                {
                                this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
                                this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                                break;
                                }
                            default:
                                {
                                this->filtercoeff_01_localop_b0 = (number)1 / (1. + this->filtercoeff_01_localop_alpha);
                                break;
                                }
                            }
                        
                            switch ((int)type) {
                            case 0:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 1:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 2:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = 0.;
                                this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 7:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = 0.;
                                this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * q * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 3:
                                {
                                this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 8:
                                {
                                this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la2 = 1.0;
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_01_localop_la0 = (1. + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_A) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_a) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 5:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = 2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1 - (this->filtercoeff_01_localop_A + 1) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = -2. * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs + this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A - 1. + (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_A * (this->filtercoeff_01_localop_A + 1. + (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = 2. * (this->filtercoeff_01_localop_A - 1. - (this->filtercoeff_01_localop_A + 1.) * this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (this->filtercoeff_01_localop_A + 1. - (this->filtercoeff_01_localop_A - 1.) * this->filtercoeff_01_localop_cs - this->filtercoeff_01_localop_beta * this->filtercoeff_01_localop_sn) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 9:
                                {
                                this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. - this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_la1 = (1. - this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 10:
                                {
                                this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_la2 = (1. + this->filtercoeff_01_localop_cs) * 0.5 * this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_la1 = -(1. + this->filtercoeff_01_localop_cs) * this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 11:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = 0.;
                                this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 13:
                                {
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 = 0.;
                                this->filtercoeff_01_localop_la2 = -this->filtercoeff_01_localop_alpha * gain * q * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 12:
                                {
                                this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                                this->filtercoeff_01_localop_la1 = this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la1 *= this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_lb1 *= this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_la0 = this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_la2 = this->filtercoeff_01_localop_b0g;
                                break;
                                }
                            case 14:
                                {
                                this->filtercoeff_01_localop_b0g = (number)1 / (this->filtercoeff_01_localop_one_over_gain + this->filtercoeff_01_localop_alpha * this->filtercoeff_01_localop_one_over_gain);
                                this->filtercoeff_01_localop_la0 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_la1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0g;
                                this->filtercoeff_01_localop_la2 = gain;
                                this->filtercoeff_01_localop_lb1 = -2. * this->filtercoeff_01_localop_cs * this->filtercoeff_01_localop_b0;
                                this->filtercoeff_01_localop_lb2 = (1. - this->filtercoeff_01_localop_alpha) * this->filtercoeff_01_localop_b0;
                                break;
                                }
                            case 15:
                                {
                                this->filtercoeff_01_localop_la0 = 1;
                                this->filtercoeff_01_localop_la1 = 0;
                                this->filtercoeff_01_localop_la2 = 0;
                                this->filtercoeff_01_localop_lb1 = 0;
                                this->filtercoeff_01_localop_lb2 = 0;
                                }
                            default:
                                {
                                break;
                                }
                            }
                        
                            return {
                                this->filtercoeff_01_localop_la0,
                                this->filtercoeff_01_localop_la1,
                                this->filtercoeff_01_localop_la2,
                                this->filtercoeff_01_localop_lb1,
                                this->filtercoeff_01_localop_lb2
                            };
                        }
                        
                        void filtercoeff_01_localop_dspsetup() {
                            this->filtercoeff_01_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
                        }
                        
                        void filtercoeff_01_localop_reset() {
                            this->filtercoeff_01_localop_twopi_over_sr = 0;
                            this->filtercoeff_01_localop_cs = 0;
                            this->filtercoeff_01_localop_sn = 0;
                            this->filtercoeff_01_localop_one_over_gain = 0;
                            this->filtercoeff_01_localop_one_over_q = 0;
                            this->filtercoeff_01_localop_alpha = 0;
                            this->filtercoeff_01_localop_beta = 0;
                            this->filtercoeff_01_localop_b0 = 0;
                            this->filtercoeff_01_localop_b0g = 0;
                            this->filtercoeff_01_localop_A = 0;
                            this->filtercoeff_01_localop_one_over_a = 0;
                            this->filtercoeff_01_localop_la0 = 0;
                            this->filtercoeff_01_localop_la1 = 0;
                            this->filtercoeff_01_localop_la2 = 0;
                            this->filtercoeff_01_localop_lb1 = 0;
                            this->filtercoeff_01_localop_lb2 = 0;
                        }
                        
                        void filtercoeff_01_updateTerms(number local_frequency, number local_gain, number local_q) {
                            if ((bool)(this->filtercoeff_01_force_update) || local_frequency != this->filtercoeff_01_last_frequency || local_q != this->filtercoeff_01_last_q || local_gain != this->filtercoeff_01_last_gain || this->filtercoeff_01_type != this->filtercoeff_01_last_type) {
                                array<number, 5> tmp = this->filtercoeff_01_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_01_type);
                                this->filtercoeff_01_la0 = tmp[0];
                                this->filtercoeff_01_la1 = tmp[1];
                                this->filtercoeff_01_la2 = tmp[2];
                                this->filtercoeff_01_lb1 = tmp[3];
                                this->filtercoeff_01_lb2 = tmp[4];
                                this->filtercoeff_01_last_frequency = local_frequency;
                                this->filtercoeff_01_last_q = local_q;
                                this->filtercoeff_01_last_gain = local_gain;
                                this->filtercoeff_01_last_type = this->filtercoeff_01_type;
                                this->filtercoeff_01_force_update = false;
                            }
                        }
                        
                        void filtercoeff_01_dspsetup(bool force) {
                            if ((bool)(this->filtercoeff_01_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            {
                                this->filtercoeff_01_activeResamp = this->vectorsize();
                            }
                        
                            this->filtercoeff_01_resamp_counter = 0;
                            this->filtercoeff_01_la0 = 0.;
                            this->filtercoeff_01_la1 = 0.;
                            this->filtercoeff_01_la2 = 0.;
                            this->filtercoeff_01_lb1 = 0.;
                            this->filtercoeff_01_lb2 = 0.;
                            this->filtercoeff_01_last_frequency = -1.;
                            this->filtercoeff_01_last_q = -1.;
                            this->filtercoeff_01_last_gain = -1.;
                            this->filtercoeff_01_last_type = this->filtercoeff_01_type;
                            this->filtercoeff_01_force_update = true;
                            this->filtercoeff_01_setupDone = true;
                            this->filtercoeff_01_localop_dspsetup();
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            biquad_tilde_01_x = 0;
                            biquad_tilde_01_a0 = 0;
                            biquad_tilde_01_a1 = 0;
                            biquad_tilde_01_a2 = 0;
                            biquad_tilde_01_b1 = 0;
                            biquad_tilde_01_b2 = 0;
                            filtercoeff_01_frequency = 1000;
                            filtercoeff_01_gain = 1;
                            filtercoeff_01_q = 1;
                            filtercoeff_01_type = 0;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            signals[1] = nullptr;
                            signals[2] = nullptr;
                            signals[3] = nullptr;
                            signals[4] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            biquad_tilde_01_x1 = 0;
                            biquad_tilde_01_x2 = 0;
                            biquad_tilde_01_y1 = 0;
                            biquad_tilde_01_y2 = 0;
                            biquad_tilde_01_setupDone = false;
                            filtercoeff_01_K_EPSILON = 1e-9;
                            filtercoeff_01_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number biquad_tilde_01_x;
                            number biquad_tilde_01_a0;
                            number biquad_tilde_01_a1;
                            number biquad_tilde_01_a2;
                            number biquad_tilde_01_b1;
                            number biquad_tilde_01_b2;
                            number filtercoeff_01_frequency;
                            number filtercoeff_01_gain;
                            number filtercoeff_01_q;
                            Int filtercoeff_01_type;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[5];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            number biquad_tilde_01_x1;
                            number biquad_tilde_01_x2;
                            number biquad_tilde_01_y1;
                            number biquad_tilde_01_y2;
                            bool biquad_tilde_01_setupDone;
                            number filtercoeff_01_resamp_counter;
                            number filtercoeff_01_activeResamp;
                            number filtercoeff_01_K_EPSILON;
                            number filtercoeff_01_la0;
                            number filtercoeff_01_la1;
                            number filtercoeff_01_la2;
                            number filtercoeff_01_lb1;
                            number filtercoeff_01_lb2;
                            number filtercoeff_01_last_frequency;
                            number filtercoeff_01_last_q;
                            number filtercoeff_01_last_gain;
                            Int filtercoeff_01_last_type;
                            bool filtercoeff_01_force_update;
                            number filtercoeff_01_localop_twopi_over_sr;
                            number filtercoeff_01_localop_cs;
                            number filtercoeff_01_localop_sn;
                            number filtercoeff_01_localop_one_over_gain;
                            number filtercoeff_01_localop_one_over_q;
                            number filtercoeff_01_localop_alpha;
                            number filtercoeff_01_localop_beta;
                            number filtercoeff_01_localop_b0;
                            number filtercoeff_01_localop_b0g;
                            number filtercoeff_01_localop_A;
                            number filtercoeff_01_localop_one_over_a;
                            number filtercoeff_01_localop_la0;
                            number filtercoeff_01_localop_la1;
                            number filtercoeff_01_localop_la2;
                            number filtercoeff_01_localop_lb1;
                            number filtercoeff_01_localop_lb2;
                            bool filtercoeff_01_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_58 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_65;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_58()
                        {
                        }
                        
                        ~RNBOSubpatcher_58()
                        {
                        }
                        
                        virtual RNBOSubpatcher_65* getPatcher() const {
                            return static_cast<RNBOSubpatcher_65 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                        }
                        
                        inline number safesqrt(number num) {
                            return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
                        }
                        
                        Index vectorsize() const {
                            return this->vs;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                            const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                            const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                            const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
                        
                            this->filtercoeff_02_perform(
                                in2,
                                this->filtercoeff_02_gain,
                                in3,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                n
                            );
                        
                            this->biquad_tilde_02_perform(
                                in1,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                out1,
                                n
                            );
                        
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 5; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            this->filtercoeff_02_dspsetup(forceDSPSetup);
                            this->biquad_tilde_02_dspsetup(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& ) {}
                        
                        void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 0;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
                        
                        void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                        
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                        }
                        
                        protected:
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 3;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 1;
                        }
                        
                        void initializeObjects() {}
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {}
                        
                        void allocateDataRefs() {}
                        
                        void filtercoeff_02_perform(
                            const Sample * frequency,
                            number gain,
                            const Sample * q,
                            SampleValue * a0,
                            SampleValue * a1,
                            SampleValue * a2,
                            SampleValue * b1,
                            SampleValue * b2,
                            Index n
                        ) {
                            RNBO_UNUSED(gain);
                            auto __filtercoeff_02_activeResamp = this->filtercoeff_02_activeResamp;
                            auto __filtercoeff_02_resamp_counter = this->filtercoeff_02_resamp_counter;
                            auto __filtercoeff_02_K_EPSILON = this->filtercoeff_02_K_EPSILON;
                        
                            for (Index i = 0; i < n; i++) {
                                number local_q = q[(Index)i];
                                number local_gain = 1;
                        
                                if (local_gain < 0)
                                    local_gain = 0;
                        
                                number local_frequency = frequency[(Index)i];
                        
                                if (local_q < __filtercoeff_02_K_EPSILON)
                                    local_q = __filtercoeff_02_K_EPSILON;
                        
                                local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
                                __filtercoeff_02_resamp_counter--;
                        
                                if (__filtercoeff_02_resamp_counter <= 0) {
                                    __filtercoeff_02_resamp_counter = __filtercoeff_02_activeResamp;
                                    this->filtercoeff_02_updateTerms(local_frequency, local_gain, local_q);
                                }
                        
                                a0[(Index)i] = this->filtercoeff_02_la0;
                                a1[(Index)i] = this->filtercoeff_02_la1;
                                a2[(Index)i] = this->filtercoeff_02_la2;
                                b1[(Index)i] = this->filtercoeff_02_lb1;
                                b2[(Index)i] = this->filtercoeff_02_lb2;
                            }
                        
                            this->filtercoeff_02_resamp_counter = __filtercoeff_02_resamp_counter;
                        }
                        
                        void biquad_tilde_02_perform(
                            const Sample * x,
                            const Sample * a0,
                            const Sample * a1,
                            const Sample * a2,
                            const Sample * b1,
                            const Sample * b2,
                            SampleValue * out1,
                            Index n
                        ) {
                            auto __biquad_tilde_02_y2 = this->biquad_tilde_02_y2;
                            auto __biquad_tilde_02_y1 = this->biquad_tilde_02_y1;
                            auto __biquad_tilde_02_x2 = this->biquad_tilde_02_x2;
                            auto __biquad_tilde_02_x1 = this->biquad_tilde_02_x1;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_02_x1 * a1[(Index)i] + __biquad_tilde_02_x2 * a2[(Index)i] - (__biquad_tilde_02_y1 * b1[(Index)i] + __biquad_tilde_02_y2 * b2[(Index)i]);
                                __biquad_tilde_02_x2 = __biquad_tilde_02_x1;
                                __biquad_tilde_02_x1 = x[(Index)i];
                                __biquad_tilde_02_y2 = __biquad_tilde_02_y1;
                                __biquad_tilde_02_y1 = tmp;
                                out1[(Index)i] = tmp;
                            }
                        
                            this->biquad_tilde_02_x1 = __biquad_tilde_02_x1;
                            this->biquad_tilde_02_x2 = __biquad_tilde_02_x2;
                            this->biquad_tilde_02_y1 = __biquad_tilde_02_y1;
                            this->biquad_tilde_02_y2 = __biquad_tilde_02_y2;
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void biquad_tilde_02_reset() {
                            this->biquad_tilde_02_x1 = 0;
                            this->biquad_tilde_02_x2 = 0;
                            this->biquad_tilde_02_y1 = 0;
                            this->biquad_tilde_02_y2 = 0;
                        }
                        
                        void biquad_tilde_02_dspsetup(bool force) {
                            if ((bool)(this->biquad_tilde_02_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->biquad_tilde_02_reset();
                            this->biquad_tilde_02_setupDone = true;
                        }
                        
                        array<number, 5> filtercoeff_02_localop_next(number frequency, number q, number gain, number type) {
                            number omega = frequency * this->filtercoeff_02_localop_twopi_over_sr;
                            this->filtercoeff_02_localop_cs = rnbo_cos(omega);
                            this->filtercoeff_02_localop_sn = rnbo_sin(omega);
                            this->filtercoeff_02_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
                            this->filtercoeff_02_localop_one_over_q = (number)1 / q;
                            this->filtercoeff_02_localop_alpha = this->filtercoeff_02_localop_sn * 0.5 * this->filtercoeff_02_localop_one_over_q;
                        
                            switch ((int)type) {
                            case 5:
                                {
                                this->filtercoeff_02_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_02_localop_beta = this->safesqrt(
                                    (this->filtercoeff_02_localop_A * this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_one_over_q - (this->filtercoeff_02_localop_A - 1.) * (this->filtercoeff_02_localop_A - 1.)
                                );
                        
                                this->filtercoeff_02_localop_b0 = (number)1 / (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn);
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_02_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_02_localop_beta = this->safesqrt(
                                    (this->filtercoeff_02_localop_A * this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_one_over_q - (this->filtercoeff_02_localop_A - 1.) * (this->filtercoeff_02_localop_A - 1.)
                                );
                        
                                this->filtercoeff_02_localop_b0 = (number)1 / (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn);
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_02_localop_A = this->safesqrt(gain);
                                this->filtercoeff_02_localop_one_over_a = (this->filtercoeff_02_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_02_localop_A);
                                this->filtercoeff_02_localop_b0 = (number)1 / (1. + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_a);
                                break;
                                }
                            case 9:
                            case 10:
                            case 11:
                            case 13:
                            case 14:
                                {
                                this->filtercoeff_02_localop_b0 = (number)1 / (1. + this->filtercoeff_02_localop_alpha);
                                this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
                                break;
                                }
                            default:
                                {
                                this->filtercoeff_02_localop_b0 = (number)1 / (1. + this->filtercoeff_02_localop_alpha);
                                break;
                                }
                            }
                        
                            switch ((int)type) {
                            case 0:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. - this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = (1. - this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 1:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. + this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = -(1. + this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 2:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = 0.;
                                this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 7:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * q * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = 0.;
                                this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * q * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 3:
                                {
                                this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 8:
                                {
                                this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = this->filtercoeff_02_localop_la0 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la2 = 1.0;
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_02_localop_la0 = (1. + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_A) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la2 = (1. - this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_A) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_a) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 5:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = 2. * this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A - 1 - (this->filtercoeff_02_localop_A + 1) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = -2. * (this->filtercoeff_02_localop_A - 1. + (this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs + this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = -2. * this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A - 1. + (this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_A * (this->filtercoeff_02_localop_A + 1. + (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = 2. * (this->filtercoeff_02_localop_A - 1. - (this->filtercoeff_02_localop_A + 1.) * this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (this->filtercoeff_02_localop_A + 1. - (this->filtercoeff_02_localop_A - 1.) * this->filtercoeff_02_localop_cs - this->filtercoeff_02_localop_beta * this->filtercoeff_02_localop_sn) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 9:
                                {
                                this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. - this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_la1 = (1. - this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 10:
                                {
                                this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_la2 = (1. + this->filtercoeff_02_localop_cs) * 0.5 * this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_la1 = -(1. + this->filtercoeff_02_localop_cs) * this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 11:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * gain * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = 0.;
                                this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * gain * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 13:
                                {
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_alpha * gain * q * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 = 0.;
                                this->filtercoeff_02_localop_la2 = -this->filtercoeff_02_localop_alpha * gain * q * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 12:
                                {
                                this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
                                this->filtercoeff_02_localop_la1 = this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la1 *= this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_lb1 *= this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_la0 = this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_la2 = this->filtercoeff_02_localop_b0g;
                                break;
                                }
                            case 14:
                                {
                                this->filtercoeff_02_localop_b0g = (number)1 / (this->filtercoeff_02_localop_one_over_gain + this->filtercoeff_02_localop_alpha * this->filtercoeff_02_localop_one_over_gain);
                                this->filtercoeff_02_localop_la0 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_la1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0g;
                                this->filtercoeff_02_localop_la2 = gain;
                                this->filtercoeff_02_localop_lb1 = -2. * this->filtercoeff_02_localop_cs * this->filtercoeff_02_localop_b0;
                                this->filtercoeff_02_localop_lb2 = (1. - this->filtercoeff_02_localop_alpha) * this->filtercoeff_02_localop_b0;
                                break;
                                }
                            case 15:
                                {
                                this->filtercoeff_02_localop_la0 = 1;
                                this->filtercoeff_02_localop_la1 = 0;
                                this->filtercoeff_02_localop_la2 = 0;
                                this->filtercoeff_02_localop_lb1 = 0;
                                this->filtercoeff_02_localop_lb2 = 0;
                                }
                            default:
                                {
                                break;
                                }
                            }
                        
                            return {
                                this->filtercoeff_02_localop_la0,
                                this->filtercoeff_02_localop_la1,
                                this->filtercoeff_02_localop_la2,
                                this->filtercoeff_02_localop_lb1,
                                this->filtercoeff_02_localop_lb2
                            };
                        }
                        
                        void filtercoeff_02_localop_dspsetup() {
                            this->filtercoeff_02_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
                        }
                        
                        void filtercoeff_02_localop_reset() {
                            this->filtercoeff_02_localop_twopi_over_sr = 0;
                            this->filtercoeff_02_localop_cs = 0;
                            this->filtercoeff_02_localop_sn = 0;
                            this->filtercoeff_02_localop_one_over_gain = 0;
                            this->filtercoeff_02_localop_one_over_q = 0;
                            this->filtercoeff_02_localop_alpha = 0;
                            this->filtercoeff_02_localop_beta = 0;
                            this->filtercoeff_02_localop_b0 = 0;
                            this->filtercoeff_02_localop_b0g = 0;
                            this->filtercoeff_02_localop_A = 0;
                            this->filtercoeff_02_localop_one_over_a = 0;
                            this->filtercoeff_02_localop_la0 = 0;
                            this->filtercoeff_02_localop_la1 = 0;
                            this->filtercoeff_02_localop_la2 = 0;
                            this->filtercoeff_02_localop_lb1 = 0;
                            this->filtercoeff_02_localop_lb2 = 0;
                        }
                        
                        void filtercoeff_02_updateTerms(number local_frequency, number local_gain, number local_q) {
                            if ((bool)(this->filtercoeff_02_force_update) || local_frequency != this->filtercoeff_02_last_frequency || local_q != this->filtercoeff_02_last_q || local_gain != this->filtercoeff_02_last_gain || this->filtercoeff_02_type != this->filtercoeff_02_last_type) {
                                array<number, 5> tmp = this->filtercoeff_02_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_02_type);
                                this->filtercoeff_02_la0 = tmp[0];
                                this->filtercoeff_02_la1 = tmp[1];
                                this->filtercoeff_02_la2 = tmp[2];
                                this->filtercoeff_02_lb1 = tmp[3];
                                this->filtercoeff_02_lb2 = tmp[4];
                                this->filtercoeff_02_last_frequency = local_frequency;
                                this->filtercoeff_02_last_q = local_q;
                                this->filtercoeff_02_last_gain = local_gain;
                                this->filtercoeff_02_last_type = this->filtercoeff_02_type;
                                this->filtercoeff_02_force_update = false;
                            }
                        }
                        
                        void filtercoeff_02_dspsetup(bool force) {
                            if ((bool)(this->filtercoeff_02_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            {
                                this->filtercoeff_02_activeResamp = this->vectorsize();
                            }
                        
                            this->filtercoeff_02_resamp_counter = 0;
                            this->filtercoeff_02_la0 = 0.;
                            this->filtercoeff_02_la1 = 0.;
                            this->filtercoeff_02_la2 = 0.;
                            this->filtercoeff_02_lb1 = 0.;
                            this->filtercoeff_02_lb2 = 0.;
                            this->filtercoeff_02_last_frequency = -1.;
                            this->filtercoeff_02_last_q = -1.;
                            this->filtercoeff_02_last_gain = -1.;
                            this->filtercoeff_02_last_type = this->filtercoeff_02_type;
                            this->filtercoeff_02_force_update = true;
                            this->filtercoeff_02_setupDone = true;
                            this->filtercoeff_02_localop_dspsetup();
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            biquad_tilde_02_x = 0;
                            biquad_tilde_02_a0 = 0;
                            biquad_tilde_02_a1 = 0;
                            biquad_tilde_02_a2 = 0;
                            biquad_tilde_02_b1 = 0;
                            biquad_tilde_02_b2 = 0;
                            filtercoeff_02_frequency = 1000;
                            filtercoeff_02_gain = 1;
                            filtercoeff_02_q = 1;
                            filtercoeff_02_type = 1;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            signals[1] = nullptr;
                            signals[2] = nullptr;
                            signals[3] = nullptr;
                            signals[4] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            biquad_tilde_02_x1 = 0;
                            biquad_tilde_02_x2 = 0;
                            biquad_tilde_02_y1 = 0;
                            biquad_tilde_02_y2 = 0;
                            biquad_tilde_02_setupDone = false;
                            filtercoeff_02_K_EPSILON = 1e-9;
                            filtercoeff_02_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number biquad_tilde_02_x;
                            number biquad_tilde_02_a0;
                            number biquad_tilde_02_a1;
                            number biquad_tilde_02_a2;
                            number biquad_tilde_02_b1;
                            number biquad_tilde_02_b2;
                            number filtercoeff_02_frequency;
                            number filtercoeff_02_gain;
                            number filtercoeff_02_q;
                            Int filtercoeff_02_type;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[5];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            number biquad_tilde_02_x1;
                            number biquad_tilde_02_x2;
                            number biquad_tilde_02_y1;
                            number biquad_tilde_02_y2;
                            bool biquad_tilde_02_setupDone;
                            number filtercoeff_02_resamp_counter;
                            number filtercoeff_02_activeResamp;
                            number filtercoeff_02_K_EPSILON;
                            number filtercoeff_02_la0;
                            number filtercoeff_02_la1;
                            number filtercoeff_02_la2;
                            number filtercoeff_02_lb1;
                            number filtercoeff_02_lb2;
                            number filtercoeff_02_last_frequency;
                            number filtercoeff_02_last_q;
                            number filtercoeff_02_last_gain;
                            Int filtercoeff_02_last_type;
                            bool filtercoeff_02_force_update;
                            number filtercoeff_02_localop_twopi_over_sr;
                            number filtercoeff_02_localop_cs;
                            number filtercoeff_02_localop_sn;
                            number filtercoeff_02_localop_one_over_gain;
                            number filtercoeff_02_localop_one_over_q;
                            number filtercoeff_02_localop_alpha;
                            number filtercoeff_02_localop_beta;
                            number filtercoeff_02_localop_b0;
                            number filtercoeff_02_localop_b0g;
                            number filtercoeff_02_localop_A;
                            number filtercoeff_02_localop_one_over_a;
                            number filtercoeff_02_localop_la0;
                            number filtercoeff_02_localop_la1;
                            number filtercoeff_02_localop_la2;
                            number filtercoeff_02_localop_lb1;
                            number filtercoeff_02_localop_lb2;
                            bool filtercoeff_02_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_59 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_65;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_59()
                        {
                        }
                        
                        ~RNBOSubpatcher_59()
                        {
                        }
                        
                        virtual RNBOSubpatcher_65* getPatcher() const {
                            return static_cast<RNBOSubpatcher_65 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                        }
                        
                        inline number safesqrt(number num) {
                            return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
                        }
                        
                        Index vectorsize() const {
                            return this->vs;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                            const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                            const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                            const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
                        
                            this->filtercoeff_03_perform(
                                in2,
                                this->filtercoeff_03_gain,
                                in3,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                n
                            );
                        
                            this->biquad_tilde_03_perform(
                                in1,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                out1,
                                n
                            );
                        
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 5; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            this->filtercoeff_03_dspsetup(forceDSPSetup);
                            this->biquad_tilde_03_dspsetup(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& ) {}
                        
                        void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 0;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
                        
                        void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                        
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                        }
                        
                        protected:
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 3;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 1;
                        }
                        
                        void initializeObjects() {}
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {}
                        
                        void allocateDataRefs() {}
                        
                        void filtercoeff_03_perform(
                            const Sample * frequency,
                            number gain,
                            const Sample * q,
                            SampleValue * a0,
                            SampleValue * a1,
                            SampleValue * a2,
                            SampleValue * b1,
                            SampleValue * b2,
                            Index n
                        ) {
                            RNBO_UNUSED(gain);
                            auto __filtercoeff_03_activeResamp = this->filtercoeff_03_activeResamp;
                            auto __filtercoeff_03_resamp_counter = this->filtercoeff_03_resamp_counter;
                            auto __filtercoeff_03_K_EPSILON = this->filtercoeff_03_K_EPSILON;
                        
                            for (Index i = 0; i < n; i++) {
                                number local_q = q[(Index)i];
                                number local_gain = 1;
                        
                                if (local_gain < 0)
                                    local_gain = 0;
                        
                                number local_frequency = frequency[(Index)i];
                        
                                if (local_q < __filtercoeff_03_K_EPSILON)
                                    local_q = __filtercoeff_03_K_EPSILON;
                        
                                local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
                                __filtercoeff_03_resamp_counter--;
                        
                                if (__filtercoeff_03_resamp_counter <= 0) {
                                    __filtercoeff_03_resamp_counter = __filtercoeff_03_activeResamp;
                                    this->filtercoeff_03_updateTerms(local_frequency, local_gain, local_q);
                                }
                        
                                a0[(Index)i] = this->filtercoeff_03_la0;
                                a1[(Index)i] = this->filtercoeff_03_la1;
                                a2[(Index)i] = this->filtercoeff_03_la2;
                                b1[(Index)i] = this->filtercoeff_03_lb1;
                                b2[(Index)i] = this->filtercoeff_03_lb2;
                            }
                        
                            this->filtercoeff_03_resamp_counter = __filtercoeff_03_resamp_counter;
                        }
                        
                        void biquad_tilde_03_perform(
                            const Sample * x,
                            const Sample * a0,
                            const Sample * a1,
                            const Sample * a2,
                            const Sample * b1,
                            const Sample * b2,
                            SampleValue * out1,
                            Index n
                        ) {
                            auto __biquad_tilde_03_y2 = this->biquad_tilde_03_y2;
                            auto __biquad_tilde_03_y1 = this->biquad_tilde_03_y1;
                            auto __biquad_tilde_03_x2 = this->biquad_tilde_03_x2;
                            auto __biquad_tilde_03_x1 = this->biquad_tilde_03_x1;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_03_x1 * a1[(Index)i] + __biquad_tilde_03_x2 * a2[(Index)i] - (__biquad_tilde_03_y1 * b1[(Index)i] + __biquad_tilde_03_y2 * b2[(Index)i]);
                                __biquad_tilde_03_x2 = __biquad_tilde_03_x1;
                                __biquad_tilde_03_x1 = x[(Index)i];
                                __biquad_tilde_03_y2 = __biquad_tilde_03_y1;
                                __biquad_tilde_03_y1 = tmp;
                                out1[(Index)i] = tmp;
                            }
                        
                            this->biquad_tilde_03_x1 = __biquad_tilde_03_x1;
                            this->biquad_tilde_03_x2 = __biquad_tilde_03_x2;
                            this->biquad_tilde_03_y1 = __biquad_tilde_03_y1;
                            this->biquad_tilde_03_y2 = __biquad_tilde_03_y2;
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void biquad_tilde_03_reset() {
                            this->biquad_tilde_03_x1 = 0;
                            this->biquad_tilde_03_x2 = 0;
                            this->biquad_tilde_03_y1 = 0;
                            this->biquad_tilde_03_y2 = 0;
                        }
                        
                        void biquad_tilde_03_dspsetup(bool force) {
                            if ((bool)(this->biquad_tilde_03_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->biquad_tilde_03_reset();
                            this->biquad_tilde_03_setupDone = true;
                        }
                        
                        array<number, 5> filtercoeff_03_localop_next(number frequency, number q, number gain, number type) {
                            number omega = frequency * this->filtercoeff_03_localop_twopi_over_sr;
                            this->filtercoeff_03_localop_cs = rnbo_cos(omega);
                            this->filtercoeff_03_localop_sn = rnbo_sin(omega);
                            this->filtercoeff_03_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
                            this->filtercoeff_03_localop_one_over_q = (number)1 / q;
                            this->filtercoeff_03_localop_alpha = this->filtercoeff_03_localop_sn * 0.5 * this->filtercoeff_03_localop_one_over_q;
                        
                            switch ((int)type) {
                            case 5:
                                {
                                this->filtercoeff_03_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_03_localop_beta = this->safesqrt(
                                    (this->filtercoeff_03_localop_A * this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_one_over_q - (this->filtercoeff_03_localop_A - 1.) * (this->filtercoeff_03_localop_A - 1.)
                                );
                        
                                this->filtercoeff_03_localop_b0 = (number)1 / (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn);
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_03_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_03_localop_beta = this->safesqrt(
                                    (this->filtercoeff_03_localop_A * this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_one_over_q - (this->filtercoeff_03_localop_A - 1.) * (this->filtercoeff_03_localop_A - 1.)
                                );
                        
                                this->filtercoeff_03_localop_b0 = (number)1 / (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn);
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_03_localop_A = this->safesqrt(gain);
                                this->filtercoeff_03_localop_one_over_a = (this->filtercoeff_03_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_03_localop_A);
                                this->filtercoeff_03_localop_b0 = (number)1 / (1. + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_a);
                                break;
                                }
                            case 9:
                            case 10:
                            case 11:
                            case 13:
                            case 14:
                                {
                                this->filtercoeff_03_localop_b0 = (number)1 / (1. + this->filtercoeff_03_localop_alpha);
                                this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
                                break;
                                }
                            default:
                                {
                                this->filtercoeff_03_localop_b0 = (number)1 / (1. + this->filtercoeff_03_localop_alpha);
                                break;
                                }
                            }
                        
                            switch ((int)type) {
                            case 0:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. - this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = (1. - this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 1:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. + this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = -(1. + this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 2:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = 0.;
                                this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 7:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * q * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = 0.;
                                this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * q * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 3:
                                {
                                this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 8:
                                {
                                this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = this->filtercoeff_03_localop_la0 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la2 = 1.0;
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_03_localop_la0 = (1. + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_A) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la2 = (1. - this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_A) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_a) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 5:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = 2. * this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A - 1 - (this->filtercoeff_03_localop_A + 1) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = -2. * (this->filtercoeff_03_localop_A - 1. + (this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs + this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = -2. * this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A - 1. + (this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_A * (this->filtercoeff_03_localop_A + 1. + (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = 2. * (this->filtercoeff_03_localop_A - 1. - (this->filtercoeff_03_localop_A + 1.) * this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (this->filtercoeff_03_localop_A + 1. - (this->filtercoeff_03_localop_A - 1.) * this->filtercoeff_03_localop_cs - this->filtercoeff_03_localop_beta * this->filtercoeff_03_localop_sn) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 9:
                                {
                                this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. - this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_la1 = (1. - this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 10:
                                {
                                this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_la2 = (1. + this->filtercoeff_03_localop_cs) * 0.5 * this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_la1 = -(1. + this->filtercoeff_03_localop_cs) * this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 11:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * gain * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = 0.;
                                this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * gain * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 13:
                                {
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_alpha * gain * q * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 = 0.;
                                this->filtercoeff_03_localop_la2 = -this->filtercoeff_03_localop_alpha * gain * q * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 12:
                                {
                                this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
                                this->filtercoeff_03_localop_la1 = this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la1 *= this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_lb1 *= this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_la0 = this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_la2 = this->filtercoeff_03_localop_b0g;
                                break;
                                }
                            case 14:
                                {
                                this->filtercoeff_03_localop_b0g = (number)1 / (this->filtercoeff_03_localop_one_over_gain + this->filtercoeff_03_localop_alpha * this->filtercoeff_03_localop_one_over_gain);
                                this->filtercoeff_03_localop_la0 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_la1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0g;
                                this->filtercoeff_03_localop_la2 = gain;
                                this->filtercoeff_03_localop_lb1 = -2. * this->filtercoeff_03_localop_cs * this->filtercoeff_03_localop_b0;
                                this->filtercoeff_03_localop_lb2 = (1. - this->filtercoeff_03_localop_alpha) * this->filtercoeff_03_localop_b0;
                                break;
                                }
                            case 15:
                                {
                                this->filtercoeff_03_localop_la0 = 1;
                                this->filtercoeff_03_localop_la1 = 0;
                                this->filtercoeff_03_localop_la2 = 0;
                                this->filtercoeff_03_localop_lb1 = 0;
                                this->filtercoeff_03_localop_lb2 = 0;
                                }
                            default:
                                {
                                break;
                                }
                            }
                        
                            return {
                                this->filtercoeff_03_localop_la0,
                                this->filtercoeff_03_localop_la1,
                                this->filtercoeff_03_localop_la2,
                                this->filtercoeff_03_localop_lb1,
                                this->filtercoeff_03_localop_lb2
                            };
                        }
                        
                        void filtercoeff_03_localop_dspsetup() {
                            this->filtercoeff_03_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
                        }
                        
                        void filtercoeff_03_localop_reset() {
                            this->filtercoeff_03_localop_twopi_over_sr = 0;
                            this->filtercoeff_03_localop_cs = 0;
                            this->filtercoeff_03_localop_sn = 0;
                            this->filtercoeff_03_localop_one_over_gain = 0;
                            this->filtercoeff_03_localop_one_over_q = 0;
                            this->filtercoeff_03_localop_alpha = 0;
                            this->filtercoeff_03_localop_beta = 0;
                            this->filtercoeff_03_localop_b0 = 0;
                            this->filtercoeff_03_localop_b0g = 0;
                            this->filtercoeff_03_localop_A = 0;
                            this->filtercoeff_03_localop_one_over_a = 0;
                            this->filtercoeff_03_localop_la0 = 0;
                            this->filtercoeff_03_localop_la1 = 0;
                            this->filtercoeff_03_localop_la2 = 0;
                            this->filtercoeff_03_localop_lb1 = 0;
                            this->filtercoeff_03_localop_lb2 = 0;
                        }
                        
                        void filtercoeff_03_updateTerms(number local_frequency, number local_gain, number local_q) {
                            if ((bool)(this->filtercoeff_03_force_update) || local_frequency != this->filtercoeff_03_last_frequency || local_q != this->filtercoeff_03_last_q || local_gain != this->filtercoeff_03_last_gain || this->filtercoeff_03_type != this->filtercoeff_03_last_type) {
                                array<number, 5> tmp = this->filtercoeff_03_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_03_type);
                                this->filtercoeff_03_la0 = tmp[0];
                                this->filtercoeff_03_la1 = tmp[1];
                                this->filtercoeff_03_la2 = tmp[2];
                                this->filtercoeff_03_lb1 = tmp[3];
                                this->filtercoeff_03_lb2 = tmp[4];
                                this->filtercoeff_03_last_frequency = local_frequency;
                                this->filtercoeff_03_last_q = local_q;
                                this->filtercoeff_03_last_gain = local_gain;
                                this->filtercoeff_03_last_type = this->filtercoeff_03_type;
                                this->filtercoeff_03_force_update = false;
                            }
                        }
                        
                        void filtercoeff_03_dspsetup(bool force) {
                            if ((bool)(this->filtercoeff_03_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            {
                                this->filtercoeff_03_activeResamp = this->vectorsize();
                            }
                        
                            this->filtercoeff_03_resamp_counter = 0;
                            this->filtercoeff_03_la0 = 0.;
                            this->filtercoeff_03_la1 = 0.;
                            this->filtercoeff_03_la2 = 0.;
                            this->filtercoeff_03_lb1 = 0.;
                            this->filtercoeff_03_lb2 = 0.;
                            this->filtercoeff_03_last_frequency = -1.;
                            this->filtercoeff_03_last_q = -1.;
                            this->filtercoeff_03_last_gain = -1.;
                            this->filtercoeff_03_last_type = this->filtercoeff_03_type;
                            this->filtercoeff_03_force_update = true;
                            this->filtercoeff_03_setupDone = true;
                            this->filtercoeff_03_localop_dspsetup();
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            biquad_tilde_03_x = 0;
                            biquad_tilde_03_a0 = 0;
                            biquad_tilde_03_a1 = 0;
                            biquad_tilde_03_a2 = 0;
                            biquad_tilde_03_b1 = 0;
                            biquad_tilde_03_b2 = 0;
                            filtercoeff_03_frequency = 1000;
                            filtercoeff_03_gain = 1;
                            filtercoeff_03_q = 1;
                            filtercoeff_03_type = 2;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            signals[1] = nullptr;
                            signals[2] = nullptr;
                            signals[3] = nullptr;
                            signals[4] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            biquad_tilde_03_x1 = 0;
                            biquad_tilde_03_x2 = 0;
                            biquad_tilde_03_y1 = 0;
                            biquad_tilde_03_y2 = 0;
                            biquad_tilde_03_setupDone = false;
                            filtercoeff_03_K_EPSILON = 1e-9;
                            filtercoeff_03_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number biquad_tilde_03_x;
                            number biquad_tilde_03_a0;
                            number biquad_tilde_03_a1;
                            number biquad_tilde_03_a2;
                            number biquad_tilde_03_b1;
                            number biquad_tilde_03_b2;
                            number filtercoeff_03_frequency;
                            number filtercoeff_03_gain;
                            number filtercoeff_03_q;
                            Int filtercoeff_03_type;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[5];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            number biquad_tilde_03_x1;
                            number biquad_tilde_03_x2;
                            number biquad_tilde_03_y1;
                            number biquad_tilde_03_y2;
                            bool biquad_tilde_03_setupDone;
                            number filtercoeff_03_resamp_counter;
                            number filtercoeff_03_activeResamp;
                            number filtercoeff_03_K_EPSILON;
                            number filtercoeff_03_la0;
                            number filtercoeff_03_la1;
                            number filtercoeff_03_la2;
                            number filtercoeff_03_lb1;
                            number filtercoeff_03_lb2;
                            number filtercoeff_03_last_frequency;
                            number filtercoeff_03_last_q;
                            number filtercoeff_03_last_gain;
                            Int filtercoeff_03_last_type;
                            bool filtercoeff_03_force_update;
                            number filtercoeff_03_localop_twopi_over_sr;
                            number filtercoeff_03_localop_cs;
                            number filtercoeff_03_localop_sn;
                            number filtercoeff_03_localop_one_over_gain;
                            number filtercoeff_03_localop_one_over_q;
                            number filtercoeff_03_localop_alpha;
                            number filtercoeff_03_localop_beta;
                            number filtercoeff_03_localop_b0;
                            number filtercoeff_03_localop_b0g;
                            number filtercoeff_03_localop_A;
                            number filtercoeff_03_localop_one_over_a;
                            number filtercoeff_03_localop_la0;
                            number filtercoeff_03_localop_la1;
                            number filtercoeff_03_localop_la2;
                            number filtercoeff_03_localop_lb1;
                            number filtercoeff_03_localop_lb2;
                            bool filtercoeff_03_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_60 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_65;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_60()
                        {
                        }
                        
                        ~RNBOSubpatcher_60()
                        {
                        }
                        
                        virtual RNBOSubpatcher_65* getPatcher() const {
                            return static_cast<RNBOSubpatcher_65 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                        }
                        
                        inline number safesqrt(number num) {
                            return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
                        }
                        
                        Index vectorsize() const {
                            return this->vs;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                            const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                            const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                            const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
                        
                            this->filtercoeff_04_perform(
                                in2,
                                this->filtercoeff_04_gain,
                                in3,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                n
                            );
                        
                            this->biquad_tilde_04_perform(
                                in1,
                                this->signals[0],
                                this->signals[1],
                                this->signals[2],
                                this->signals[3],
                                this->signals[4],
                                out1,
                                n
                            );
                        
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 5; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            this->filtercoeff_04_dspsetup(forceDSPSetup);
                            this->biquad_tilde_04_dspsetup(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& ) {}
                        
                        void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 0;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
                        
                        void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                        
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                        }
                        
                        protected:
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 3;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 1;
                        }
                        
                        void initializeObjects() {}
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {}
                        
                        void allocateDataRefs() {}
                        
                        void filtercoeff_04_perform(
                            const Sample * frequency,
                            number gain,
                            const Sample * q,
                            SampleValue * a0,
                            SampleValue * a1,
                            SampleValue * a2,
                            SampleValue * b1,
                            SampleValue * b2,
                            Index n
                        ) {
                            RNBO_UNUSED(gain);
                            auto __filtercoeff_04_activeResamp = this->filtercoeff_04_activeResamp;
                            auto __filtercoeff_04_resamp_counter = this->filtercoeff_04_resamp_counter;
                            auto __filtercoeff_04_K_EPSILON = this->filtercoeff_04_K_EPSILON;
                        
                            for (Index i = 0; i < n; i++) {
                                number local_q = q[(Index)i];
                                number local_gain = 1;
                        
                                if (local_gain < 0)
                                    local_gain = 0;
                        
                                number local_frequency = frequency[(Index)i];
                        
                                if (local_q < __filtercoeff_04_K_EPSILON)
                                    local_q = __filtercoeff_04_K_EPSILON;
                        
                                local_frequency = (local_frequency > this->sr * 0.5 ? this->sr * 0.5 : (local_frequency < 1 ? 1 : local_frequency));
                                __filtercoeff_04_resamp_counter--;
                        
                                if (__filtercoeff_04_resamp_counter <= 0) {
                                    __filtercoeff_04_resamp_counter = __filtercoeff_04_activeResamp;
                                    this->filtercoeff_04_updateTerms(local_frequency, local_gain, local_q);
                                }
                        
                                a0[(Index)i] = this->filtercoeff_04_la0;
                                a1[(Index)i] = this->filtercoeff_04_la1;
                                a2[(Index)i] = this->filtercoeff_04_la2;
                                b1[(Index)i] = this->filtercoeff_04_lb1;
                                b2[(Index)i] = this->filtercoeff_04_lb2;
                            }
                        
                            this->filtercoeff_04_resamp_counter = __filtercoeff_04_resamp_counter;
                        }
                        
                        void biquad_tilde_04_perform(
                            const Sample * x,
                            const Sample * a0,
                            const Sample * a1,
                            const Sample * a2,
                            const Sample * b1,
                            const Sample * b2,
                            SampleValue * out1,
                            Index n
                        ) {
                            auto __biquad_tilde_04_y2 = this->biquad_tilde_04_y2;
                            auto __biquad_tilde_04_y1 = this->biquad_tilde_04_y1;
                            auto __biquad_tilde_04_x2 = this->biquad_tilde_04_x2;
                            auto __biquad_tilde_04_x1 = this->biquad_tilde_04_x1;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number tmp = x[(Index)i] * a0[(Index)i] + __biquad_tilde_04_x1 * a1[(Index)i] + __biquad_tilde_04_x2 * a2[(Index)i] - (__biquad_tilde_04_y1 * b1[(Index)i] + __biquad_tilde_04_y2 * b2[(Index)i]);
                                __biquad_tilde_04_x2 = __biquad_tilde_04_x1;
                                __biquad_tilde_04_x1 = x[(Index)i];
                                __biquad_tilde_04_y2 = __biquad_tilde_04_y1;
                                __biquad_tilde_04_y1 = tmp;
                                out1[(Index)i] = tmp;
                            }
                        
                            this->biquad_tilde_04_x1 = __biquad_tilde_04_x1;
                            this->biquad_tilde_04_x2 = __biquad_tilde_04_x2;
                            this->biquad_tilde_04_y1 = __biquad_tilde_04_y1;
                            this->biquad_tilde_04_y2 = __biquad_tilde_04_y2;
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void biquad_tilde_04_reset() {
                            this->biquad_tilde_04_x1 = 0;
                            this->biquad_tilde_04_x2 = 0;
                            this->biquad_tilde_04_y1 = 0;
                            this->biquad_tilde_04_y2 = 0;
                        }
                        
                        void biquad_tilde_04_dspsetup(bool force) {
                            if ((bool)(this->biquad_tilde_04_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->biquad_tilde_04_reset();
                            this->biquad_tilde_04_setupDone = true;
                        }
                        
                        array<number, 5> filtercoeff_04_localop_next(number frequency, number q, number gain, number type) {
                            number omega = frequency * this->filtercoeff_04_localop_twopi_over_sr;
                            this->filtercoeff_04_localop_cs = rnbo_cos(omega);
                            this->filtercoeff_04_localop_sn = rnbo_sin(omega);
                            this->filtercoeff_04_localop_one_over_gain = (gain >= 0 ? (number)1 / gain : 0.0);
                            this->filtercoeff_04_localop_one_over_q = (number)1 / q;
                            this->filtercoeff_04_localop_alpha = this->filtercoeff_04_localop_sn * 0.5 * this->filtercoeff_04_localop_one_over_q;
                        
                            switch ((int)type) {
                            case 5:
                                {
                                this->filtercoeff_04_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_04_localop_beta = this->safesqrt(
                                    (this->filtercoeff_04_localop_A * this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_one_over_q - (this->filtercoeff_04_localop_A - 1.) * (this->filtercoeff_04_localop_A - 1.)
                                );
                        
                                this->filtercoeff_04_localop_b0 = (number)1 / (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn);
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_04_localop_A = this->safesqrt(gain);
                        
                                this->filtercoeff_04_localop_beta = this->safesqrt(
                                    (this->filtercoeff_04_localop_A * this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_one_over_q - (this->filtercoeff_04_localop_A - 1.) * (this->filtercoeff_04_localop_A - 1.)
                                );
                        
                                this->filtercoeff_04_localop_b0 = (number)1 / (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn);
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_04_localop_A = this->safesqrt(gain);
                                this->filtercoeff_04_localop_one_over_a = (this->filtercoeff_04_localop_A == 0 ? 0 : (number)1 / this->filtercoeff_04_localop_A);
                                this->filtercoeff_04_localop_b0 = (number)1 / (1. + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_a);
                                break;
                                }
                            case 9:
                            case 10:
                            case 11:
                            case 13:
                            case 14:
                                {
                                this->filtercoeff_04_localop_b0 = (number)1 / (1. + this->filtercoeff_04_localop_alpha);
                                this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
                                break;
                                }
                            default:
                                {
                                this->filtercoeff_04_localop_b0 = (number)1 / (1. + this->filtercoeff_04_localop_alpha);
                                break;
                                }
                            }
                        
                            switch ((int)type) {
                            case 0:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. - this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = (1. - this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 1:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. + this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = -(1. + this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 2:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = 0.;
                                this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 7:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * q * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = 0.;
                                this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * q * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 3:
                                {
                                this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 8:
                                {
                                this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = this->filtercoeff_04_localop_la0 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la2 = 1.0;
                                break;
                                }
                            case 4:
                                {
                                this->filtercoeff_04_localop_la0 = (1. + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_A) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la2 = (1. - this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_A) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_a) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 5:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = 2. * this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A - 1 - (this->filtercoeff_04_localop_A + 1) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = -2. * (this->filtercoeff_04_localop_A - 1. + (this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 6:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs + this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = -2. * this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A - 1. + (this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_A * (this->filtercoeff_04_localop_A + 1. + (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = 2. * (this->filtercoeff_04_localop_A - 1. - (this->filtercoeff_04_localop_A + 1.) * this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (this->filtercoeff_04_localop_A + 1. - (this->filtercoeff_04_localop_A - 1.) * this->filtercoeff_04_localop_cs - this->filtercoeff_04_localop_beta * this->filtercoeff_04_localop_sn) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 9:
                                {
                                this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. - this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_la1 = (1. - this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 10:
                                {
                                this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_la2 = (1. + this->filtercoeff_04_localop_cs) * 0.5 * this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_la1 = -(1. + this->filtercoeff_04_localop_cs) * this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 11:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * gain * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = 0.;
                                this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * gain * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 13:
                                {
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_alpha * gain * q * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 = 0.;
                                this->filtercoeff_04_localop_la2 = -this->filtercoeff_04_localop_alpha * gain * q * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 12:
                                {
                                this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
                                this->filtercoeff_04_localop_la1 = this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la1 *= this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_lb1 *= this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_la0 = this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_la2 = this->filtercoeff_04_localop_b0g;
                                break;
                                }
                            case 14:
                                {
                                this->filtercoeff_04_localop_b0g = (number)1 / (this->filtercoeff_04_localop_one_over_gain + this->filtercoeff_04_localop_alpha * this->filtercoeff_04_localop_one_over_gain);
                                this->filtercoeff_04_localop_la0 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_la1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0g;
                                this->filtercoeff_04_localop_la2 = gain;
                                this->filtercoeff_04_localop_lb1 = -2. * this->filtercoeff_04_localop_cs * this->filtercoeff_04_localop_b0;
                                this->filtercoeff_04_localop_lb2 = (1. - this->filtercoeff_04_localop_alpha) * this->filtercoeff_04_localop_b0;
                                break;
                                }
                            case 15:
                                {
                                this->filtercoeff_04_localop_la0 = 1;
                                this->filtercoeff_04_localop_la1 = 0;
                                this->filtercoeff_04_localop_la2 = 0;
                                this->filtercoeff_04_localop_lb1 = 0;
                                this->filtercoeff_04_localop_lb2 = 0;
                                }
                            default:
                                {
                                break;
                                }
                            }
                        
                            return {
                                this->filtercoeff_04_localop_la0,
                                this->filtercoeff_04_localop_la1,
                                this->filtercoeff_04_localop_la2,
                                this->filtercoeff_04_localop_lb1,
                                this->filtercoeff_04_localop_lb2
                            };
                        }
                        
                        void filtercoeff_04_localop_dspsetup() {
                            this->filtercoeff_04_localop_twopi_over_sr = (number)6.283185307179586 / this->sr;
                        }
                        
                        void filtercoeff_04_localop_reset() {
                            this->filtercoeff_04_localop_twopi_over_sr = 0;
                            this->filtercoeff_04_localop_cs = 0;
                            this->filtercoeff_04_localop_sn = 0;
                            this->filtercoeff_04_localop_one_over_gain = 0;
                            this->filtercoeff_04_localop_one_over_q = 0;
                            this->filtercoeff_04_localop_alpha = 0;
                            this->filtercoeff_04_localop_beta = 0;
                            this->filtercoeff_04_localop_b0 = 0;
                            this->filtercoeff_04_localop_b0g = 0;
                            this->filtercoeff_04_localop_A = 0;
                            this->filtercoeff_04_localop_one_over_a = 0;
                            this->filtercoeff_04_localop_la0 = 0;
                            this->filtercoeff_04_localop_la1 = 0;
                            this->filtercoeff_04_localop_la2 = 0;
                            this->filtercoeff_04_localop_lb1 = 0;
                            this->filtercoeff_04_localop_lb2 = 0;
                        }
                        
                        void filtercoeff_04_updateTerms(number local_frequency, number local_gain, number local_q) {
                            if ((bool)(this->filtercoeff_04_force_update) || local_frequency != this->filtercoeff_04_last_frequency || local_q != this->filtercoeff_04_last_q || local_gain != this->filtercoeff_04_last_gain || this->filtercoeff_04_type != this->filtercoeff_04_last_type) {
                                array<number, 5> tmp = this->filtercoeff_04_localop_next(local_frequency, local_q, local_gain, this->filtercoeff_04_type);
                                this->filtercoeff_04_la0 = tmp[0];
                                this->filtercoeff_04_la1 = tmp[1];
                                this->filtercoeff_04_la2 = tmp[2];
                                this->filtercoeff_04_lb1 = tmp[3];
                                this->filtercoeff_04_lb2 = tmp[4];
                                this->filtercoeff_04_last_frequency = local_frequency;
                                this->filtercoeff_04_last_q = local_q;
                                this->filtercoeff_04_last_gain = local_gain;
                                this->filtercoeff_04_last_type = this->filtercoeff_04_type;
                                this->filtercoeff_04_force_update = false;
                            }
                        }
                        
                        void filtercoeff_04_dspsetup(bool force) {
                            if ((bool)(this->filtercoeff_04_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            {
                                this->filtercoeff_04_activeResamp = this->vectorsize();
                            }
                        
                            this->filtercoeff_04_resamp_counter = 0;
                            this->filtercoeff_04_la0 = 0.;
                            this->filtercoeff_04_la1 = 0.;
                            this->filtercoeff_04_la2 = 0.;
                            this->filtercoeff_04_lb1 = 0.;
                            this->filtercoeff_04_lb2 = 0.;
                            this->filtercoeff_04_last_frequency = -1.;
                            this->filtercoeff_04_last_q = -1.;
                            this->filtercoeff_04_last_gain = -1.;
                            this->filtercoeff_04_last_type = this->filtercoeff_04_type;
                            this->filtercoeff_04_force_update = true;
                            this->filtercoeff_04_setupDone = true;
                            this->filtercoeff_04_localop_dspsetup();
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            biquad_tilde_04_x = 0;
                            biquad_tilde_04_a0 = 0;
                            biquad_tilde_04_a1 = 0;
                            biquad_tilde_04_a2 = 0;
                            biquad_tilde_04_b1 = 0;
                            biquad_tilde_04_b2 = 0;
                            filtercoeff_04_frequency = 1000;
                            filtercoeff_04_gain = 1;
                            filtercoeff_04_q = 1;
                            filtercoeff_04_type = 3;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            signals[1] = nullptr;
                            signals[2] = nullptr;
                            signals[3] = nullptr;
                            signals[4] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            biquad_tilde_04_x1 = 0;
                            biquad_tilde_04_x2 = 0;
                            biquad_tilde_04_y1 = 0;
                            biquad_tilde_04_y2 = 0;
                            biquad_tilde_04_setupDone = false;
                            filtercoeff_04_K_EPSILON = 1e-9;
                            filtercoeff_04_setupDone = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number biquad_tilde_04_x;
                            number biquad_tilde_04_a0;
                            number biquad_tilde_04_a1;
                            number biquad_tilde_04_a2;
                            number biquad_tilde_04_b1;
                            number biquad_tilde_04_b2;
                            number filtercoeff_04_frequency;
                            number filtercoeff_04_gain;
                            number filtercoeff_04_q;
                            Int filtercoeff_04_type;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[5];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            number biquad_tilde_04_x1;
                            number biquad_tilde_04_x2;
                            number biquad_tilde_04_y1;
                            number biquad_tilde_04_y2;
                            bool biquad_tilde_04_setupDone;
                            number filtercoeff_04_resamp_counter;
                            number filtercoeff_04_activeResamp;
                            number filtercoeff_04_K_EPSILON;
                            number filtercoeff_04_la0;
                            number filtercoeff_04_la1;
                            number filtercoeff_04_la2;
                            number filtercoeff_04_lb1;
                            number filtercoeff_04_lb2;
                            number filtercoeff_04_last_frequency;
                            number filtercoeff_04_last_q;
                            number filtercoeff_04_last_gain;
                            Int filtercoeff_04_last_type;
                            bool filtercoeff_04_force_update;
                            number filtercoeff_04_localop_twopi_over_sr;
                            number filtercoeff_04_localop_cs;
                            number filtercoeff_04_localop_sn;
                            number filtercoeff_04_localop_one_over_gain;
                            number filtercoeff_04_localop_one_over_q;
                            number filtercoeff_04_localop_alpha;
                            number filtercoeff_04_localop_beta;
                            number filtercoeff_04_localop_b0;
                            number filtercoeff_04_localop_b0g;
                            number filtercoeff_04_localop_A;
                            number filtercoeff_04_localop_one_over_a;
                            number filtercoeff_04_localop_la0;
                            number filtercoeff_04_localop_la1;
                            number filtercoeff_04_localop_la2;
                            number filtercoeff_04_localop_lb1;
                            number filtercoeff_04_localop_lb2;
                            bool filtercoeff_04_setupDone;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            RNBOSubpatcher_65()
            {
            }
            
            ~RNBOSubpatcher_65()
            {
                delete this->p_01;
                delete this->p_02;
                delete this->p_03;
                delete this->p_04;
            }
            
            virtual RNBOSubpatcher_67* getPatcher() const {
                return static_cast<RNBOSubpatcher_67 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->ip_01_perform(this->signals[0], n);
                this->ip_02_perform(this->signals[1], n);
            
                this->signalgate_01_perform(
                    this->signalgate_01_onoff,
                    in1,
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    this->signals[5],
                    n
                );
            
                this->p_01_perform(this->signals[2], this->signals[0], this->signals[1], this->signals[6], n);
                this->p_02_perform(this->signals[3], this->signals[0], this->signals[1], this->signals[2], n);
                this->p_03_perform(this->signals[4], this->signals[0], this->signals[1], this->signals[3], n);
                this->p_04_perform(this->signals[5], this->signals[0], this->signals[1], this->signals[4], n);
            
                this->selector_01_perform(
                    this->selector_01_onoff,
                    this->signals[6],
                    this->signals[2],
                    this->signals[3],
                    this->signals[4],
                    out1,
                    n
                );
            
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 7; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->ip_01_sigbuf = resizeSignal(this->ip_01_sigbuf, this->maxvs, maxBlockSize);
                    this->ip_02_sigbuf = resizeSignal(this->ip_02_sigbuf, this->maxvs, maxBlockSize);
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->ip_01_dspsetup(forceDSPSetup);
                this->ip_02_dspsetup(forceDSPSetup);
                this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
                this->p_01->setVoiceIndex(index);
                this->p_02->setVoiceIndex(index);
                this->p_03->setVoiceIndex(index);
                this->p_04->setVoiceIndex(index);
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
                this->p_01->setNoteNumber(noteNumber);
                this->p_02->setNoteNumber(noteNumber);
                this->p_03->setNoteNumber(noteNumber);
                this->p_04->setNoteNumber(noteNumber);
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {
                this->p_01 = new RNBOSubpatcher_57();
                this->p_01->setEngineAndPatcher(this->getEngine(), this);
                this->p_01->initialize();
                this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
                this->p_02 = new RNBOSubpatcher_58();
                this->p_02->setEngineAndPatcher(this->getEngine(), this);
                this->p_02->initialize();
                this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
                this->p_03 = new RNBOSubpatcher_59();
                this->p_03->setEngineAndPatcher(this->getEngine(), this);
                this->p_03->initialize();
                this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
                this->p_04 = new RNBOSubpatcher_60();
                this->p_04->setEngineAndPatcher(this->getEngine(), this);
                this->p_04->initialize();
                this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
            }
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_05_getPresetValue(getSubState(preset, "filtertype"));
                this->param_06_getPresetValue(getSubState(preset, "cutoff"));
                this->param_07_getPresetValue(getSubState(preset, "resonance_mod"));
                this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "filter.lp"));
                this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "filter.hp"));
                this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "filter.bp"));
                this->p_04->getPreset(getSubState(getSubState(preset, "__sps"), "filter.br"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_05_value_set(v);
                    break;
                    }
                case 1:
                    {
                    this->param_06_value_set(v);
                    break;
                    }
                case 2:
                    {
                    this->param_07_value_set(v);
                    break;
                    }
                default:
                    {
                    index -= 3;
            
                    if (index < this->p_01->getNumParameters())
                        this->p_01->setParameterValue(index, v, time);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        this->p_02->setParameterValue(index, v, time);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        this->p_03->setParameterValue(index, v, time);
            
                    index -= this->p_03->getNumParameters();
            
                    if (index < this->p_04->getNumParameters())
                        this->p_04->setParameterValue(index, v, time);
            
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_05_value;
                    }
                case 1:
                    {
                    return this->param_06_value;
                    }
                case 2:
                    {
                    return this->param_07_value;
                    }
                default:
                    {
                    index -= 3;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->getParameterValue(index);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterValue(index);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->getParameterValue(index);
            
                    index -= this->p_03->getNumParameters();
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->getParameterValue(index);
            
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 3 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "filtertype";
                    }
                case 1:
                    {
                    return "cutoff";
                    }
                case 2:
                    {
                    return "resonance_mod";
                    }
                default:
                    {
                    index -= 3;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->getParameterName(index);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterName(index);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->getParameterName(index);
            
                    index -= this->p_03->getNumParameters();
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->getParameterName(index);
            
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "poly/filters/filtertype";
                    }
                case 1:
                    {
                    return "poly/filters/cutoff";
                    }
                case 2:
                    {
                    return "poly/filters/resonance_mod";
                    }
                default:
                    {
                    index -= 3;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->getParameterId(index);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->getParameterId(index);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->getParameterId(index);
            
                    index -= this->p_03->getNumParameters();
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->getParameterId(index);
            
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = 0;
                        info->max = 3;
                        info->exponent = 1;
                        info->steps = 4;
                        static const char * eVal0[] = {"lowpass", "highpass", "bandpass", "bandreject"};
                        info->enumValues = eVal0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 1:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 8000;
                        info->min = 20;
                        info->max = 20000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 2:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 1;
                        info->min = 0.01;
                        info->max = 10;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    default:
                        {
                        index -= 3;
            
                        if (index < this->p_01->getNumParameters())
                            this->p_01->getParameterInfo(index, info);
            
                        index -= this->p_01->getNumParameters();
            
                        if (index < this->p_02->getNumParameters())
                            this->p_02->getParameterInfo(index, info);
            
                        index -= this->p_02->getNumParameters();
            
                        if (index < this->p_03->getNumParameters())
                            this->p_03->getParameterInfo(index, info);
            
                        index -= this->p_03->getNumParameters();
            
                        if (index < this->p_04->getNumParameters())
                            this->p_04->getParameterInfo(index, info);
            
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
                if (subpatcher == this->p_01)
                    return 3;
            
                if (subpatcher == this->p_02)
                    return 3 + this->p_01->getNumParameters();
            
                if (subpatcher == this->p_03)
                    return 3 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
            
                if (subpatcher == this->p_04)
                    return 3 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();
            
                return 0;
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 3 ? 3 : value));
                        ParameterValue normalizedValue = (value - 0) / (3 - 0);
            
                        {
                            normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 4);
                        }
            
                        return normalizedValue;
                    }
                    }
                case 1:
                    {
                    {
                        value = (value < 20 ? 20 : (value > 20000 ? 20000 : value));
                        ParameterValue normalizedValue = (value - 20) / (20000 - 20);
                        return normalizedValue;
                    }
                    }
                case 2:
                    {
                    {
                        value = (value < 0.01 ? 0.01 : (value > 10 ? 10 : value));
                        ParameterValue normalizedValue = (value - 0.01) / (10 - 0.01);
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    index -= 3;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_03->getNumParameters();
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->convertToNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 0:
                    {
                    {
                        {
                            value = this->applyStepsToNormalizedParameterValue(value, 4);
                        }
            
                        {
                            return 0 + value * (3 - 0);
                        }
                    }
                    }
                case 1:
                    {
                    {
                        {
                            return 20 + value * (20000 - 20);
                        }
                    }
                    }
                case 2:
                    {
                    {
                        {
                            return 0.01 + value * (10 - 0.01);
                        }
                    }
                    }
                default:
                    {
                    index -= 3;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_03->getNumParameters();
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->convertFromNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_05_value_constrain(value);
                    }
                case 1:
                    {
                    return this->param_06_value_constrain(value);
                    }
                case 2:
                    {
                    return this->param_07_value_constrain(value);
                    }
                default:
                    {
                    index -= 3;
            
                    if (index < this->p_01->getNumParameters())
                        return this->p_01->constrainParameterValue(index, value);
            
                    index -= this->p_01->getNumParameters();
            
                    if (index < this->p_02->getNumParameters())
                        return this->p_02->constrainParameterValue(index, value);
            
                    index -= this->p_02->getNumParameters();
            
                    if (index < this->p_03->getNumParameters())
                        return this->p_03->constrainParameterValue(index, value);
            
                    index -= this->p_03->getNumParameters();
            
                    if (index < this->p_04->getNumParameters())
                        return this->p_04->constrainParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_01->processNumMessage(tag, objectId, time, payload);
                this->p_02->processNumMessage(tag, objectId, time, payload);
                this->p_03->processNumMessage(tag, objectId, time, payload);
                this->p_04->processNumMessage(tag, objectId, time, payload);
            }
            
            void processListMessage(
                MessageTag tag,
                MessageTag objectId,
                MillisecondTime time,
                const list& payload
            ) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_01->processListMessage(tag, objectId, time, payload);
                this->p_02->processListMessage(tag, objectId, time, payload);
                this->p_03->processListMessage(tag, objectId, time, payload);
                this->p_04->processListMessage(tag, objectId, time, payload);
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_01->processBangMessage(tag, objectId, time);
                this->p_02->processBangMessage(tag, objectId, time);
                this->p_03->processBangMessage(tag, objectId, time);
                this->p_04->processBangMessage(tag, objectId, time);
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                auto subpatchResult_0 = this->p_01->resolveTag(tag);
            
                if (subpatchResult_0)
                    return subpatchResult_0;
            
                auto subpatchResult_1 = this->p_02->resolveTag(tag);
            
                if (subpatchResult_1)
                    return subpatchResult_1;
            
                auto subpatchResult_2 = this->p_03->resolveTag(tag);
            
                if (subpatchResult_2)
                    return subpatchResult_2;
            
                auto subpatchResult_3 = this->p_04->resolveTag(tag);
            
                if (subpatchResult_3)
                    return subpatchResult_3;
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->p_01->processDataViewUpdate(index, time);
                this->p_02->processDataViewUpdate(index, time);
                this->p_03->processDataViewUpdate(index, time);
                this->p_04->processDataViewUpdate(index, time);
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void param_05_value_set(number v) {
                v = this->param_05_value_constrain(v);
                this->param_05_value = v;
                this->sendParameter(0, false);
            
                if (this->param_05_value != this->param_05_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_05_lastValue = this->param_05_value;
                }
            
                this->expr_01_in1_set(v);
            }
            
            void param_06_value_set(number v) {
                v = this->param_06_value_constrain(v);
                this->param_06_value = v;
                this->sendParameter(1, false);
            
                if (this->param_06_value != this->param_06_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_06_lastValue = this->param_06_value;
                }
            
                this->ip_01_value_set(v);
            }
            
            void param_07_value_set(number v) {
                v = this->param_07_value_constrain(v);
                this->param_07_value = v;
                this->sendParameter(2, false);
            
                if (this->param_07_value != this->param_07_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_07_lastValue = this->param_07_value;
                }
            
                this->ip_02_value_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->ip_01_init();
                this->ip_02_init();
                this->p_01->initializeObjects();
                this->p_02->initializeObjects();
                this->p_03->initializeObjects();
                this->p_04->initializeObjects();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->p_01->startup();
                this->p_02->startup();
                this->p_03->startup();
                this->p_04->startup();
            
                {
                    this->scheduleParamInit(0, 0);
                }
            
                {
                    this->scheduleParamInit(1, 0);
                }
            
                {
                    this->scheduleParamInit(2, 0);
                }
            }
            
            void allocateDataRefs() {
                this->p_01->allocateDataRefs();
                this->p_02->allocateDataRefs();
                this->p_03->allocateDataRefs();
                this->p_04->allocateDataRefs();
            }
            
            number param_05_value_constrain(number v) const {
                v = (v > 3 ? 3 : (v < 0 ? 0 : v));
            
                {
                    number oneStep = (number)3 / (number)3;
                    number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
                    number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
                    v = numberOfSteps * oneStep;
                }
            
                return v;
            }
            
            void selector_01_onoff_set(number v) {
                this->selector_01_onoff = v;
            }
            
            void signalgate_01_onoff_set(number v) {
                this->signalgate_01_onoff = v;
            }
            
            void expr_01_out1_set(number v) {
                this->expr_01_out1 = v;
                this->selector_01_onoff_set(this->expr_01_out1);
                this->signalgate_01_onoff_set(this->expr_01_out1);
            }
            
            void expr_01_in1_set(number in1) {
                this->expr_01_in1 = in1;
                this->expr_01_out1_set(this->expr_01_in1 + this->expr_01_in2);//#map:filters/+_obj-11:1
            }
            
            number param_06_value_constrain(number v) const {
                v = (v > 20000 ? 20000 : (v < 20 ? 20 : v));
                return v;
            }
            
            void ip_01_value_set(number v) {
                this->ip_01_value = v;
                this->ip_01_fillSigBuf();
                this->ip_01_lastValue = v;
            }
            
            number param_07_value_constrain(number v) const {
                v = (v > 10 ? 10 : (v < 0.01 ? 0.01 : v));
                return v;
            }
            
            void ip_02_value_set(number v) {
                this->ip_02_value = v;
                this->ip_02_fillSigBuf();
                this->ip_02_lastValue = v;
            }
            
            void ip_01_perform(SampleValue * out, Index n) {
                auto __ip_01_lastValue = this->ip_01_lastValue;
                auto __ip_01_lastIndex = this->ip_01_lastIndex;
            
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = ((SampleIndex)(i) >= __ip_01_lastIndex ? __ip_01_lastValue : this->ip_01_sigbuf[(Index)i]);
                }
            
                __ip_01_lastIndex = 0;
                this->ip_01_lastIndex = __ip_01_lastIndex;
            }
            
            void ip_02_perform(SampleValue * out, Index n) {
                auto __ip_02_lastValue = this->ip_02_lastValue;
                auto __ip_02_lastIndex = this->ip_02_lastIndex;
            
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = ((SampleIndex)(i) >= __ip_02_lastIndex ? __ip_02_lastValue : this->ip_02_sigbuf[(Index)i]);
                }
            
                __ip_02_lastIndex = 0;
                this->ip_02_lastIndex = __ip_02_lastIndex;
            }
            
            void signalgate_01_perform(
                number onoff,
                const SampleValue * input,
                SampleValue * out1,
                SampleValue * out2,
                SampleValue * out3,
                SampleValue * out4,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (onoff == 1) {
                        out1[(Index)i] = input[(Index)i];
                        out2[(Index)i] = 0;
                        out3[(Index)i] = 0;
                        out4[(Index)i] = 0;
                    } else if (onoff == 2) {
                        out2[(Index)i] = input[(Index)i];
                        out1[(Index)i] = 0;
                        out3[(Index)i] = 0;
                        out4[(Index)i] = 0;
                    } else if (onoff == 3) {
                        out3[(Index)i] = input[(Index)i];
                        out1[(Index)i] = 0;
                        out2[(Index)i] = 0;
                        out4[(Index)i] = 0;
                    } else if (onoff == 4) {
                        out4[(Index)i] = input[(Index)i];
                        out1[(Index)i] = 0;
                        out2[(Index)i] = 0;
                        out3[(Index)i] = 0;
                    } else {
                        out1[(Index)i] = 0;
                        out2[(Index)i] = 0;
                        out3[(Index)i] = 0;
                        out4[(Index)i] = 0;
                    }
                }
            }
            
            void p_01_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                SampleValue * out1,
                Index n
            ) {
                // subpatcher: filter.lp
                ConstSampleArray<3> ins = {in1, in2, in3};
            
                SampleArray<1> outs = {out1};
                this->p_01->process(ins, 3, outs, 1, n);
            }
            
            void p_02_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                SampleValue * out1,
                Index n
            ) {
                // subpatcher: filter.hp
                ConstSampleArray<3> ins = {in1, in2, in3};
            
                SampleArray<1> outs = {out1};
                this->p_02->process(ins, 3, outs, 1, n);
            }
            
            void p_03_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                SampleValue * out1,
                Index n
            ) {
                // subpatcher: filter.bp
                ConstSampleArray<3> ins = {in1, in2, in3};
            
                SampleArray<1> outs = {out1};
                this->p_03->process(ins, 3, outs, 1, n);
            }
            
            void p_04_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                SampleValue * out1,
                Index n
            ) {
                // subpatcher: filter.br
                ConstSampleArray<3> ins = {in1, in2, in3};
            
                SampleArray<1> outs = {out1};
                this->p_04->process(ins, 3, outs, 1, n);
            }
            
            void selector_01_perform(
                number onoff,
                const SampleValue * in1,
                const SampleValue * in2,
                const SampleValue * in3,
                const SampleValue * in4,
                SampleValue * out,
                Index n
            ) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    if (onoff >= 1 && onoff < 2)
                        out[(Index)i] = in1[(Index)i];
                    else if (onoff >= 2 && onoff < 3)
                        out[(Index)i] = in2[(Index)i];
                    else if (onoff >= 3 && onoff < 4)
                        out[(Index)i] = in3[(Index)i];
                    else if (onoff >= 4 && onoff < 5)
                        out[(Index)i] = in4[(Index)i];
                    else
                        out[(Index)i] = 0;
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void param_05_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_05_value;
            }
            
            void param_05_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_05_value_set(preset["value"]);
            }
            
            void ip_01_init() {
                this->ip_01_lastValue = this->ip_01_value;
            }
            
            void ip_01_fillSigBuf() {
                if ((bool)(this->ip_01_sigbuf)) {
                    SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
            
                    if (k >= (SampleIndex)(this->vs))
                        k = (SampleIndex)(this->vs) - 1;
            
                    for (SampleIndex i = (SampleIndex)(this->ip_01_lastIndex); i < k; i++) {
                        if (this->ip_01_resetCount > 0) {
                            this->ip_01_sigbuf[(Index)i] = 1;
                            this->ip_01_resetCount--;
                        } else {
                            this->ip_01_sigbuf[(Index)i] = this->ip_01_lastValue;
                        }
                    }
            
                    this->ip_01_lastIndex = k;
                }
            }
            
            void ip_01_dspsetup(bool force) {
                if ((bool)(this->ip_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->ip_01_lastIndex = 0;
                this->ip_01_setupDone = true;
            }
            
            void param_06_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_06_value;
            }
            
            void param_06_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_06_value_set(preset["value"]);
            }
            
            void ip_02_init() {
                this->ip_02_lastValue = this->ip_02_value;
            }
            
            void ip_02_fillSigBuf() {
                if ((bool)(this->ip_02_sigbuf)) {
                    SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
            
                    if (k >= (SampleIndex)(this->vs))
                        k = (SampleIndex)(this->vs) - 1;
            
                    for (SampleIndex i = (SampleIndex)(this->ip_02_lastIndex); i < k; i++) {
                        if (this->ip_02_resetCount > 0) {
                            this->ip_02_sigbuf[(Index)i] = 1;
                            this->ip_02_resetCount--;
                        } else {
                            this->ip_02_sigbuf[(Index)i] = this->ip_02_lastValue;
                        }
                    }
            
                    this->ip_02_lastIndex = k;
                }
            }
            
            void ip_02_dspsetup(bool force) {
                if ((bool)(this->ip_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->ip_02_lastIndex = 0;
                this->ip_02_setupDone = true;
            }
            
            void param_07_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_07_value;
            }
            
            void param_07_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_07_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                selector_01_onoff = 1;
                expr_01_in1 = 0;
                expr_01_in2 = 1;
                expr_01_out1 = 0;
                param_05_value = 0;
                signalgate_01_onoff = 0;
                p_01_target = 0;
                ip_01_value = 0;
                ip_01_impulse = 0;
                param_06_value = 8000;
                p_02_target = 0;
                p_03_target = 0;
                p_04_target = 0;
                ip_02_value = 0;
                ip_02_impulse = 0;
                param_07_value = 1;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                signals[4] = nullptr;
                signals[5] = nullptr;
                signals[6] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                param_05_lastValue = 0;
                ip_01_lastIndex = 0;
                ip_01_lastValue = 0;
                ip_01_resetCount = 0;
                ip_01_sigbuf = nullptr;
                ip_01_setupDone = false;
                param_06_lastValue = 0;
                ip_02_lastIndex = 0;
                ip_02_lastValue = 0;
                ip_02_resetCount = 0;
                ip_02_sigbuf = nullptr;
                ip_02_setupDone = false;
                param_07_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number selector_01_onoff;
                number expr_01_in1;
                number expr_01_in2;
                number expr_01_out1;
                number param_05_value;
                number signalgate_01_onoff;
                number p_01_target;
                number ip_01_value;
                number ip_01_impulse;
                number param_06_value;
                number p_02_target;
                number p_03_target;
                number p_04_target;
                number ip_02_value;
                number ip_02_impulse;
                number param_07_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[7];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number param_05_lastValue;
                SampleIndex ip_01_lastIndex;
                number ip_01_lastValue;
                SampleIndex ip_01_resetCount;
                signal ip_01_sigbuf;
                bool ip_01_setupDone;
                number param_06_lastValue;
                SampleIndex ip_02_lastIndex;
                number ip_02_lastValue;
                SampleIndex ip_02_resetCount;
                signal ip_02_sigbuf;
                bool ip_02_setupDone;
                number param_07_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                RNBOSubpatcher_57* p_01;
                RNBOSubpatcher_58* p_02;
                RNBOSubpatcher_59* p_03;
                RNBOSubpatcher_60* p_04;
            
    };
    
    class RNBOSubpatcher_66 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_67;
            friend class rnbomatic;
            
            public:
            
            class RNBOSubpatcher_61 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_66;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_61()
                        {
                        }
                        
                        ~RNBOSubpatcher_61()
                        {
                        }
                        
                        virtual RNBOSubpatcher_66* getPatcher() const {
                            return static_cast<RNBOSubpatcher_66 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                            getEngine()->flushClockEvents(this, 2098551528, false);
                            getEngine()->flushClockEvents(this, -1494586265, false);
                        }
                        
                        Index voice() {
                            return this->_voiceIndex;
                        }
                        
                        number random(number low, number high) {
                            number range = high - low;
                            return globalrandom() * range + low;
                        }
                        
                        number samplerate() const {
                            return this->sr;
                        }
                        
                        number mstosamps(MillisecondTime ms) {
                            return ms * this->sr * 0.001;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                            SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                            const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                            const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                            this->noise_tilde_01_perform(this->signals[0], n);
                        
                            this->cycle_tilde_01_perform(
                                in1,
                                this->cycle_tilde_01_phase_offset,
                                this->signals[1],
                                this->signals[2],
                                n
                            );
                        
                            this->numbertilde_01_perform(in1, this->dummyBuffer, n);
                            this->saw_tilde_01_perform(in1, this->saw_tilde_01_syncPhase, this->signals[3], this->signals[4], n);
                        
                            this->rect_tilde_01_perform(
                                in1,
                                in2,
                                this->rect_tilde_01_syncPhase,
                                this->signals[5],
                                this->signals[6],
                                n
                            );
                        
                            this->tri_tilde_01_perform(
                                in1,
                                in2,
                                this->tri_tilde_01_syncPhase,
                                this->signals[7],
                                this->signals[8],
                                n
                            );
                        
                            this->numbertilde_02_perform(in2, this->dummyBuffer, n);
                        
                            this->rect_tilde_02_perform(
                                in1,
                                in2,
                                this->rect_tilde_02_syncPhase,
                                this->signals[9],
                                this->signals[10],
                                n
                            );
                        
                            this->selector_02_perform(
                                this->selector_02_onoff,
                                this->signals[0],
                                this->signals[1],
                                this->signals[3],
                                this->signals[7],
                                this->signals[5],
                                this->signals[9],
                                out1,
                                n
                            );
                        
                            this->ip_03_perform(this->signals[9], n);
                        
                            this->selector_03_perform(
                                this->selector_03_onoff,
                                this->signals[9],
                                this->signals[2],
                                this->signals[4],
                                this->signals[8],
                                this->signals[6],
                                this->signals[10],
                                out2,
                                n
                            );
                        
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 11; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->ip_03_sigbuf = resizeSignal(this->ip_03_sigbuf, this->maxvs, maxBlockSize);
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            this->cycle_tilde_01_dspsetup(forceDSPSetup);
                            this->numbertilde_01_dspsetup(forceDSPSetup);
                            this->saw_tilde_01_dspsetup(forceDSPSetup);
                            this->tri_tilde_01_dspsetup(forceDSPSetup);
                            this->numbertilde_02_dspsetup(forceDSPSetup);
                            this->ip_03_dspsetup(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& preset) {
                            this->param_08_getPresetValue(getSubState(preset, "mode"));
                        }
                        
                        void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                            this->updateTime(time);
                        
                            switch (index) {
                            case 0:
                                {
                                this->param_08_value_set(v);
                                break;
                                }
                            }
                        }
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            case 0:
                                {
                                return this->param_08_value;
                                }
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 1;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            case 0:
                                {
                                return "mode";
                                }
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            case 0:
                                {
                                return "poly/oscillators/oscB/mode";
                                }
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                            {
                                switch (index) {
                                case 0:
                                    {
                                    info->type = ParameterTypeNumber;
                                    info->initialValue = 2;
                                    info->min = 0;
                                    info->max = 5;
                                    info->exponent = 1;
                                    info->steps = 6;
                                    static const char * eVal0[] = {"noise", "sine", "saw", "triangle", "square", "pulse"};
                                    info->enumValues = eVal0;
                                    info->debug = false;
                                    info->saveable = true;
                                    info->transmittable = true;
                                    info->initialized = true;
                                    info->visible = true;
                                    info->displayName = "";
                                    info->unit = "";
                                    info->ioType = IOTypeUndefined;
                                    info->signalIndex = INVALID_INDEX;
                                    break;
                                    }
                                }
                            }
                        }
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            case 0:
                                {
                                {
                                    value = (value < 0 ? 0 : (value > 5 ? 5 : value));
                                    ParameterValue normalizedValue = (value - 0) / (5 - 0);
                        
                                    {
                                        normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 6);
                                    }
                        
                                    return normalizedValue;
                                }
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            case 0:
                                {
                                {
                                    {
                                        value = this->applyStepsToNormalizedParameterValue(value, 6);
                                    }
                        
                                    {
                                        return 0 + value * (5 - 0);
                                    }
                                }
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            case 0:
                                {
                                return this->param_08_value_constrain(value);
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                            RNBO_UNUSED(hasValue);
                            this->updateTime(time);
                        
                            switch (index) {
                            case 2098551528:
                                {
                                this->numbertilde_01_value_set(value);
                                break;
                                }
                            case -1494586265:
                                {
                                this->numbertilde_02_value_set(value);
                                break;
                                }
                            }
                        }
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("valin"):
                                {
                                if (TAG("poly/oscillators/oscB/number_obj-39") == objectId)
                                    this->numberobj_01_valin_set(payload);
                        
                                break;
                                }
                            case TAG("format"):
                                {
                                if (TAG("poly/oscillators/oscB/number_obj-39") == objectId)
                                    this->numberobj_01_format_set(payload);
                        
                                break;
                                }
                            case TAG("sig"):
                                {
                                if (TAG("poly/oscillators/oscB/number~_obj-18") == objectId)
                                    this->numbertilde_01_sig_number_set(payload);
                        
                                if (TAG("poly/oscillators/oscB/number~_obj-25") == objectId)
                                    this->numbertilde_02_sig_number_set(payload);
                        
                                break;
                                }
                            case TAG("mode"):
                                {
                                if (TAG("poly/oscillators/oscB/number~_obj-18") == objectId)
                                    this->numbertilde_01_mode_set(payload);
                        
                                if (TAG("poly/oscillators/oscB/number~_obj-25") == objectId)
                                    this->numbertilde_02_mode_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processListMessage(
                            MessageTag tag,
                            MessageTag objectId,
                            MillisecondTime time,
                            const list& payload
                        ) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("sig"):
                                {
                                if (TAG("poly/oscillators/oscB/number~_obj-18") == objectId)
                                    this->numbertilde_01_sig_list_set(payload);
                        
                                if (TAG("poly/oscillators/oscB/number~_obj-25") == objectId)
                                    this->numbertilde_02_sig_list_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                            case TAG("valout"):
                                {
                                return "valout";
                                }
                            case TAG("poly/oscillators/oscB/number_obj-39"):
                                {
                                return "poly/oscillators/oscB/number_obj-39";
                                }
                            case TAG("setup"):
                                {
                                return "setup";
                                }
                            case TAG("monitor"):
                                {
                                return "monitor";
                                }
                            case TAG("poly/oscillators/oscB/number~_obj-18"):
                                {
                                return "poly/oscillators/oscB/number~_obj-18";
                                }
                            case TAG("assign"):
                                {
                                return "assign";
                                }
                            case TAG("poly/oscillators/oscB/number~_obj-25"):
                                {
                                return "poly/oscillators/oscB/number~_obj-25";
                                }
                            case TAG("valin"):
                                {
                                return "valin";
                                }
                            case TAG("format"):
                                {
                                return "format";
                                }
                            case TAG("sig"):
                                {
                                return "sig";
                                }
                            case TAG("mode"):
                                {
                                return "mode";
                                }
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                            this->updateTime(time);
                        
                            if (index == 1) {
                                this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                                this->cycle_tilde_01_bufferUpdated();
                            }
                        }
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                            this->cycle_tilde_01_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                        }
                        
                        protected:
                        
                        void param_08_value_set(number v) {
                            v = this->param_08_value_constrain(v);
                            this->param_08_value = v;
                            this->sendParameter(0, false);
                        
                            if (this->param_08_value != this->param_08_lastValue) {
                                this->getEngine()->presetTouched();
                                this->param_08_lastValue = this->param_08_value;
                            }
                        
                            this->expr_02_in1_set(v);
                            this->numberobj_01_value_set(v);
                        }
                        
                        void numberobj_01_valin_set(number v) {
                            this->numberobj_01_value_set(v);
                        }
                        
                        void numberobj_01_format_set(number v) {
                            this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
                        }
                        
                        void numbertilde_01_sig_number_set(number v) {
                            this->numbertilde_01_outValue = v;
                        }
                        
                        void numbertilde_01_sig_list_set(const list& v) {
                            this->numbertilde_01_outValue = v[0];
                        }
                        
                        void numbertilde_01_mode_set(number v) {
                            if (v == 1) {
                                this->numbertilde_01_currentMode = 0;
                            } else if (v == 2) {
                                this->numbertilde_01_currentMode = 1;
                            }
                        }
                        
                        void numbertilde_02_sig_number_set(number v) {
                            this->numbertilde_02_outValue = v;
                        }
                        
                        void numbertilde_02_sig_list_set(const list& v) {
                            this->numbertilde_02_outValue = v[0];
                        }
                        
                        void numbertilde_02_mode_set(number v) {
                            if (v == 1) {
                                this->numbertilde_02_currentMode = 0;
                            } else if (v == 2) {
                                this->numbertilde_02_currentMode = 1;
                            }
                        }
                        
                        void numbertilde_01_value_set(number ) {}
                        
                        void numbertilde_02_value_set(number ) {}
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 2;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 2;
                        }
                        
                        void initializeObjects() {
                            this->numberobj_01_init();
                            this->noise_tilde_01_init();
                            this->numbertilde_01_init();
                            this->numbertilde_02_init();
                            this->ip_03_init();
                        }
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {
                            this->updateTime(this->getEngine()->getCurrentTime());
                        
                            {
                                this->scheduleParamInit(0, 0);
                            }
                        }
                        
                        void allocateDataRefs() {
                            this->cycle_tilde_01_buffer->requestSize(16384, 1);
                            this->cycle_tilde_01_buffer->setSampleRate(this->sr);
                            this->cycle_tilde_01_buffer = this->cycle_tilde_01_buffer->allocateIfNeeded();
                        }
                        
                        number param_08_value_constrain(number v) const {
                            v = (v > 5 ? 5 : (v < 0 ? 0 : v));
                        
                            {
                                number oneStep = (number)5 / (number)5;
                                number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
                                number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
                                v = numberOfSteps * oneStep;
                            }
                        
                            return v;
                        }
                        
                        void selector_03_onoff_set(number v) {
                            this->selector_03_onoff = v;
                        }
                        
                        void selector_02_onoff_set(number v) {
                            this->selector_02_onoff = v;
                        }
                        
                        void expr_02_out1_set(number v) {
                            this->expr_02_out1 = v;
                            this->selector_03_onoff_set(this->expr_02_out1);
                            this->selector_02_onoff_set(this->expr_02_out1);
                        }
                        
                        void expr_02_in1_set(number in1) {
                            this->expr_02_in1 = in1;
                            this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:oscillators/oscB/+_obj-7:1
                        }
                        
                        void numberobj_01_output_set(number ) {}
                        
                        void numberobj_01_value_set(number v) {
                            this->numberobj_01_value_setter(v);
                            v = this->numberobj_01_value;
                            number localvalue = v;
                        
                            if (this->numberobj_01_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->getEngine()->sendNumMessage(
                                TAG("valout"),
                                TAG("poly/oscillators/oscB/number_obj-39"),
                                localvalue,
                                this->_currentTime
                            );
                        
                            this->numberobj_01_output_set(localvalue);
                        }
                        
                        void noise_tilde_01_perform(SampleValue * out1, Index n) {
                            auto __noise_tilde_01_state = this->noise_tilde_01_state;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                out1[(Index)i] = xoshiro_next(__noise_tilde_01_state);
                            }
                        }
                        
                        void cycle_tilde_01_perform(
                            const Sample * frequency,
                            number phase_offset,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(phase_offset);
                            auto __cycle_tilde_01_f2i = this->cycle_tilde_01_f2i;
                            auto __cycle_tilde_01_buffer = this->cycle_tilde_01_buffer;
                            auto __cycle_tilde_01_phasei = this->cycle_tilde_01_phasei;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                {
                                    uint32_t uint_phase;
                        
                                    {
                                        {
                                            uint_phase = __cycle_tilde_01_phasei;
                                        }
                                    }
                        
                                    uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                                    number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                                    number y0 = __cycle_tilde_01_buffer[(Index)idx];
                                    number y1 = __cycle_tilde_01_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                                    number y = y0 + frac * (y1 - y0);
                        
                                    {
                                        uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_01_f2i));
                                        __cycle_tilde_01_phasei = uint32_add(__cycle_tilde_01_phasei, pincr);
                                    }
                        
                                    out1[(Index)i] = y;
                                    out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                                    continue;
                                }
                            }
                        
                            this->cycle_tilde_01_phasei = __cycle_tilde_01_phasei;
                        }
                        
                        void numbertilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
                            auto __numbertilde_01_currentIntervalInSamples = this->numbertilde_01_currentIntervalInSamples;
                            auto __numbertilde_01_lastValue = this->numbertilde_01_lastValue;
                            auto __numbertilde_01_currentInterval = this->numbertilde_01_currentInterval;
                            auto __numbertilde_01_rampInSamples = this->numbertilde_01_rampInSamples;
                            auto __numbertilde_01_outValue = this->numbertilde_01_outValue;
                            auto __numbertilde_01_currentMode = this->numbertilde_01_currentMode;
                            number monitorvalue = input_signal[0];
                        
                            for (Index i = 0; i < n; i++) {
                                if (__numbertilde_01_currentMode == 0) {
                                    output[(Index)i] = this->numbertilde_01_smooth_next(
                                        __numbertilde_01_outValue,
                                        __numbertilde_01_rampInSamples,
                                        __numbertilde_01_rampInSamples
                                    );
                                } else {
                                    output[(Index)i] = input_signal[(Index)i];
                                }
                            }
                        
                            __numbertilde_01_currentInterval -= n;
                        
                            if (monitorvalue != __numbertilde_01_lastValue && __numbertilde_01_currentInterval <= 0) {
                                __numbertilde_01_currentInterval = __numbertilde_01_currentIntervalInSamples;
                        
                                this->getEngine()->scheduleClockEventWithValue(
                                    this,
                                    2098551528,
                                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                                    monitorvalue
                                );;
                        
                                __numbertilde_01_lastValue = monitorvalue;
                        
                                this->getEngine()->sendListMessage(
                                    TAG("monitor"),
                                    TAG("poly/oscillators/oscB/number~_obj-18"),
                                    {monitorvalue},
                                    this->_currentTime
                                );;
                            }
                        
                            this->numbertilde_01_currentInterval = __numbertilde_01_currentInterval;
                            this->numbertilde_01_lastValue = __numbertilde_01_lastValue;
                        }
                        
                        void saw_tilde_01_perform(
                            const Sample * frequency,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __saw_tilde_01_didSync = this->saw_tilde_01_didSync;
                            auto __saw_tilde_01_lastSyncDiff = this->saw_tilde_01_lastSyncDiff;
                            auto __saw_tilde_01_lastSyncPhase = this->saw_tilde_01_lastSyncPhase;
                            auto __saw_tilde_01_t = this->saw_tilde_01_t;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number dt = frequency[(Index)i] / this->samplerate();
                                number t1 = __saw_tilde_01_t + 0.5;
                                t1 -= trunc(t1);
                                number y = 2 * t1 - 1;
                        
                                if (dt != 0.0) {
                                    number syncDiff = 0 - __saw_tilde_01_lastSyncPhase;
                                    __saw_tilde_01_lastSyncPhase = 0;
                                    __saw_tilde_01_lastSyncDiff = syncDiff;
                                    number lookahead = 0 + syncDiff;
                        
                                    if (t1 < dt) {
                                        number d = t1 / dt;
                                        y -= d + d - d * d - 1;
                                    } else if (t1 + dt > 1) {
                                        number d = (t1 - 1) / dt;
                                        y -= d + d + d * d + 1;
                                    } else if ((bool)(__saw_tilde_01_didSync)) {
                                        y = 0;
                                        __saw_tilde_01_didSync = false;
                                    } else if (lookahead > 1) {
                                        y *= 0.5;
                                        __saw_tilde_01_t = 0;
                                        __saw_tilde_01_didSync = true;
                                    }
                        
                                    __saw_tilde_01_t += dt;
                        
                                    if (dt > 0) {
                                        while (__saw_tilde_01_t >= 1) {
                                            __saw_tilde_01_t -= 1;
                                        }
                                    } else {
                                        while (__saw_tilde_01_t <= 0) {
                                            __saw_tilde_01_t += 1;
                                        }
                                    }
                                }
                        
                                y = this->saw_tilde_01_dcblocker_next(y, 0.9997);
                                out1[(Index)i] = 0.5 * y;
                                out2[(Index)i] = __saw_tilde_01_t;
                            }
                        
                            this->saw_tilde_01_t = __saw_tilde_01_t;
                            this->saw_tilde_01_lastSyncPhase = __saw_tilde_01_lastSyncPhase;
                            this->saw_tilde_01_lastSyncDiff = __saw_tilde_01_lastSyncDiff;
                            this->saw_tilde_01_didSync = __saw_tilde_01_didSync;
                        }
                        
                        void rect_tilde_01_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __rect_tilde_01_xHistory = this->rect_tilde_01_xHistory;
                            auto __rect_tilde_01_yHistory = this->rect_tilde_01_yHistory;
                            auto __rect_tilde_01_didSync = this->rect_tilde_01_didSync;
                            auto __rect_tilde_01_t = this->rect_tilde_01_t;
                            auto __rect_tilde_01_lastSyncDiff = this->rect_tilde_01_lastSyncDiff;
                            auto __rect_tilde_01_lastSyncPhase = this->rect_tilde_01_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                                number pw = pulsewidth[(Index)i];
                        
                                if (pulsewidth[(Index)i] > 0.99) {
                                    pw = 0.99;
                                } else if (pulsewidth[(Index)i] < 0.01) {
                                    pw = 0.01;
                                }
                        
                                number syncDiff = 0 - __rect_tilde_01_lastSyncPhase;
                                __rect_tilde_01_lastSyncPhase = 0;
                                __rect_tilde_01_lastSyncDiff = syncDiff;
                                number syncLookahead = 0 + syncDiff;
                                number tCurr = __rect_tilde_01_t;
                                number tPrev = tCurr - dt;
                                number tNext = tCurr + dt;
                        
                                if (tPrev < 0) {
                                    while (tPrev < 0) {
                                        tPrev += 1;
                                    }
                                }
                        
                                if (tNext > 1) {
                                    while (tNext >= 1) {
                                        tNext -= 1;
                                    }
                                }
                        
                                number yNext = this->rect_tilde_01_rectangle(tNext, pw);
                                number yCurr = this->rect_tilde_01_rectangle(tCurr, pw);
                                number yPrev = this->rect_tilde_01_rectangle(tPrev, pw);
                        
                                if (dt != 0.0) {
                                    if (yPrev < yCurr) {
                                        number d = tCurr / dt;
                                        yCurr += d - 0.5 * d * d - 0.5;
                                    } else if (yCurr < yNext) {
                                        number d = (1 - tCurr) / dt;
                                        yCurr += 0.5 * d * d + d + 0.5;
                                    } else if (yPrev > yCurr) {
                                        number d = (tCurr - pw) / dt;
                                        yCurr -= d - 0.5 * d * d - 0.5;
                                    } else if (yCurr > yNext) {
                                        number d = (pw - tCurr) / dt;
                                        yCurr -= 0.5 * d * d + d + 0.5;
                                    } else if ((bool)(__rect_tilde_01_didSync)) {
                                        yCurr = 0.25;
                                        __rect_tilde_01_didSync = false;
                                    } else if (syncLookahead > 1) {
                                        if (yCurr < 0) {
                                            yCurr = -0.125;
                                        }
                        
                                        __rect_tilde_01_t = 0;
                                        __rect_tilde_01_didSync = true;
                                    }
                        
                                    __rect_tilde_01_t += dt;
                        
                                    if (dt > 0) {
                                        while (__rect_tilde_01_t >= 1) {
                                            __rect_tilde_01_t -= 1;
                                        }
                                    } else {
                                        while (__rect_tilde_01_t <= 0) {
                                            __rect_tilde_01_t += 1;
                                        }
                                    }
                                }
                        
                                number output = yCurr - __rect_tilde_01_yHistory + __rect_tilde_01_xHistory * 0.9997;
                                __rect_tilde_01_xHistory = output;
                                __rect_tilde_01_yHistory = yCurr;
                                out1[(Index)i] = 0.5 * output;
                                out2[(Index)i] = __rect_tilde_01_t;
                            }
                        
                            this->rect_tilde_01_lastSyncPhase = __rect_tilde_01_lastSyncPhase;
                            this->rect_tilde_01_lastSyncDiff = __rect_tilde_01_lastSyncDiff;
                            this->rect_tilde_01_t = __rect_tilde_01_t;
                            this->rect_tilde_01_didSync = __rect_tilde_01_didSync;
                            this->rect_tilde_01_yHistory = __rect_tilde_01_yHistory;
                            this->rect_tilde_01_xHistory = __rect_tilde_01_xHistory;
                        }
                        
                        void tri_tilde_01_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __tri_tilde_01_yn3 = this->tri_tilde_01_yn3;
                            auto __tri_tilde_01_yn2 = this->tri_tilde_01_yn2;
                            auto __tri_tilde_01_yn1 = this->tri_tilde_01_yn1;
                            auto __tri_tilde_01_app_correction = this->tri_tilde_01_app_correction;
                            auto __tri_tilde_01_flg = this->tri_tilde_01_flg;
                            auto __tri_tilde_01_yn = this->tri_tilde_01_yn;
                            auto __tri_tilde_01_t = this->tri_tilde_01_t;
                            auto __tri_tilde_01_lastSyncDiff = this->tri_tilde_01_lastSyncDiff;
                            auto __tri_tilde_01_lastSyncPhase = this->tri_tilde_01_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                        
                                if (dt != 0.0) {
                                    number pw = pulsewidth[(Index)i];
                        
                                    if (pulsewidth[(Index)i] > 0.99) {
                                        pw = 0.99;
                                    } else if (pulsewidth[(Index)i] < 0.01) {
                                        pw = 0.01;
                                    }
                        
                                    number syncDiff = 0 - __tri_tilde_01_lastSyncPhase;
                                    __tri_tilde_01_lastSyncPhase = 0;
                                    __tri_tilde_01_lastSyncDiff = syncDiff;
                                    number syncLookahead = 0 + syncDiff;
                        
                                    if (syncLookahead > 1) {
                                        __tri_tilde_01_t = 0;
                                    }
                        
                                    number tCurr = __tri_tilde_01_t;
                                    number upSlope = __frequency / (pw * this->samplerate());
                                    number downSlope = __frequency / ((1 - pw) * this->samplerate());
                        
                                    if (tCurr <= pw) {
                                        __tri_tilde_01_yn = (number)2 / pw * tCurr - 1;
                        
                                        if (__tri_tilde_01_flg == -1) {
                                            __tri_tilde_01_app_correction = 1;
                                            __tri_tilde_01_flg = 1;
                                        } else if (__tri_tilde_01_app_correction == 1) {
                                            __tri_tilde_01_app_correction = 0;
                                            number d = (tCurr - dt) / dt;
                                            number d2 = d * d;
                                            number d3 = d2 * d;
                                            number d4 = d2 * d2;
                                            number d5 = d * d4;
                                            number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                            number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                            number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                            number h3 = d5 / (number)120;
                                            __tri_tilde_01_yn += upSlope * h0;
                                            __tri_tilde_01_yn1 += upSlope * h1;
                                            __tri_tilde_01_yn2 += upSlope * h2;
                                            __tri_tilde_01_yn3 += upSlope * h3;
                                        }
                        
                                        __tri_tilde_01_flg = 1;
                                    } else {
                                        __tri_tilde_01_yn = 1 - 2 * (tCurr - pw) / (1 - pw);
                        
                                        if (__tri_tilde_01_flg == 1) {
                                            __tri_tilde_01_app_correction = 1;
                                        } else if (__tri_tilde_01_app_correction == 1) {
                                            __tri_tilde_01_app_correction = 0;
                                            number d = (tCurr - pw - dt) / dt;
                                            number d2 = d * d;
                                            number d3 = d2 * d;
                                            number d4 = d2 * d2;
                                            number d5 = d4 * d;
                                            number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                            number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                            number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                            number h3 = d5 / (number)120;
                                            __tri_tilde_01_yn -= downSlope * h0;
                                            __tri_tilde_01_yn1 -= downSlope * h1;
                                            __tri_tilde_01_yn2 -= downSlope * h2;
                                            __tri_tilde_01_yn3 -= downSlope * h3;
                                        }
                        
                                        __tri_tilde_01_flg = -1;
                                    }
                                }
                        
                                number y = __tri_tilde_01_yn3;
                                __tri_tilde_01_yn3 = __tri_tilde_01_yn2;
                                __tri_tilde_01_yn2 = __tri_tilde_01_yn1;
                                __tri_tilde_01_yn1 = __tri_tilde_01_yn;
                                __tri_tilde_01_t += dt;
                        
                                if (dt > 0) {
                                    while (__tri_tilde_01_t >= 1) {
                                        __tri_tilde_01_t -= 1;
                                    }
                                } else {
                                    while (__tri_tilde_01_t <= 0) {
                                        __tri_tilde_01_t += 1;
                                    }
                                }
                        
                                y = this->tri_tilde_01_dcblocker_next(y, 0.9997);
                                out1[(Index)i] = y * 0.5;
                                out2[(Index)i] = __tri_tilde_01_t;
                            }
                        
                            this->tri_tilde_01_lastSyncPhase = __tri_tilde_01_lastSyncPhase;
                            this->tri_tilde_01_lastSyncDiff = __tri_tilde_01_lastSyncDiff;
                            this->tri_tilde_01_t = __tri_tilde_01_t;
                            this->tri_tilde_01_yn = __tri_tilde_01_yn;
                            this->tri_tilde_01_flg = __tri_tilde_01_flg;
                            this->tri_tilde_01_app_correction = __tri_tilde_01_app_correction;
                            this->tri_tilde_01_yn1 = __tri_tilde_01_yn1;
                            this->tri_tilde_01_yn2 = __tri_tilde_01_yn2;
                            this->tri_tilde_01_yn3 = __tri_tilde_01_yn3;
                        }
                        
                        void numbertilde_02_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
                            auto __numbertilde_02_currentIntervalInSamples = this->numbertilde_02_currentIntervalInSamples;
                            auto __numbertilde_02_lastValue = this->numbertilde_02_lastValue;
                            auto __numbertilde_02_currentInterval = this->numbertilde_02_currentInterval;
                            auto __numbertilde_02_rampInSamples = this->numbertilde_02_rampInSamples;
                            auto __numbertilde_02_outValue = this->numbertilde_02_outValue;
                            auto __numbertilde_02_currentMode = this->numbertilde_02_currentMode;
                            number monitorvalue = input_signal[0];
                        
                            for (Index i = 0; i < n; i++) {
                                if (__numbertilde_02_currentMode == 0) {
                                    output[(Index)i] = this->numbertilde_02_smooth_next(
                                        __numbertilde_02_outValue,
                                        __numbertilde_02_rampInSamples,
                                        __numbertilde_02_rampInSamples
                                    );
                                } else {
                                    output[(Index)i] = input_signal[(Index)i];
                                }
                            }
                        
                            __numbertilde_02_currentInterval -= n;
                        
                            if (monitorvalue != __numbertilde_02_lastValue && __numbertilde_02_currentInterval <= 0) {
                                __numbertilde_02_currentInterval = __numbertilde_02_currentIntervalInSamples;
                        
                                this->getEngine()->scheduleClockEventWithValue(
                                    this,
                                    -1494586265,
                                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                                    monitorvalue
                                );;
                        
                                __numbertilde_02_lastValue = monitorvalue;
                        
                                this->getEngine()->sendListMessage(
                                    TAG("monitor"),
                                    TAG("poly/oscillators/oscB/number~_obj-25"),
                                    {monitorvalue},
                                    this->_currentTime
                                );;
                            }
                        
                            this->numbertilde_02_currentInterval = __numbertilde_02_currentInterval;
                            this->numbertilde_02_lastValue = __numbertilde_02_lastValue;
                        }
                        
                        void rect_tilde_02_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __rect_tilde_02_xHistory = this->rect_tilde_02_xHistory;
                            auto __rect_tilde_02_yHistory = this->rect_tilde_02_yHistory;
                            auto __rect_tilde_02_didSync = this->rect_tilde_02_didSync;
                            auto __rect_tilde_02_t = this->rect_tilde_02_t;
                            auto __rect_tilde_02_lastSyncDiff = this->rect_tilde_02_lastSyncDiff;
                            auto __rect_tilde_02_lastSyncPhase = this->rect_tilde_02_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                                number pw = pulsewidth[(Index)i];
                        
                                if (pulsewidth[(Index)i] > 0.99) {
                                    pw = 0.99;
                                } else if (pulsewidth[(Index)i] < 0.01) {
                                    pw = 0.01;
                                }
                        
                                number syncDiff = 0 - __rect_tilde_02_lastSyncPhase;
                                __rect_tilde_02_lastSyncPhase = 0;
                                __rect_tilde_02_lastSyncDiff = syncDiff;
                                number syncLookahead = 0 + syncDiff;
                                number tCurr = __rect_tilde_02_t;
                                number tPrev = tCurr - dt;
                                number tNext = tCurr + dt;
                        
                                if (tPrev < 0) {
                                    while (tPrev < 0) {
                                        tPrev += 1;
                                    }
                                }
                        
                                if (tNext > 1) {
                                    while (tNext >= 1) {
                                        tNext -= 1;
                                    }
                                }
                        
                                number yNext = this->rect_tilde_02_rectangle(tNext, pw);
                                number yCurr = this->rect_tilde_02_rectangle(tCurr, pw);
                                number yPrev = this->rect_tilde_02_rectangle(tPrev, pw);
                        
                                if (dt != 0.0) {
                                    if (yPrev < yCurr) {
                                        number d = tCurr / dt;
                                        yCurr += d - 0.5 * d * d - 0.5;
                                    } else if (yCurr < yNext) {
                                        number d = (1 - tCurr) / dt;
                                        yCurr += 0.5 * d * d + d + 0.5;
                                    } else if (yPrev > yCurr) {
                                        number d = (tCurr - pw) / dt;
                                        yCurr -= d - 0.5 * d * d - 0.5;
                                    } else if (yCurr > yNext) {
                                        number d = (pw - tCurr) / dt;
                                        yCurr -= 0.5 * d * d + d + 0.5;
                                    } else if ((bool)(__rect_tilde_02_didSync)) {
                                        yCurr = 0.25;
                                        __rect_tilde_02_didSync = false;
                                    } else if (syncLookahead > 1) {
                                        if (yCurr < 0) {
                                            yCurr = -0.125;
                                        }
                        
                                        __rect_tilde_02_t = 0;
                                        __rect_tilde_02_didSync = true;
                                    }
                        
                                    __rect_tilde_02_t += dt;
                        
                                    if (dt > 0) {
                                        while (__rect_tilde_02_t >= 1) {
                                            __rect_tilde_02_t -= 1;
                                        }
                                    } else {
                                        while (__rect_tilde_02_t <= 0) {
                                            __rect_tilde_02_t += 1;
                                        }
                                    }
                                }
                        
                                number output = yCurr - __rect_tilde_02_yHistory + __rect_tilde_02_xHistory * 0.9997;
                                __rect_tilde_02_xHistory = output;
                                __rect_tilde_02_yHistory = yCurr;
                                out1[(Index)i] = 0.5 * output;
                                out2[(Index)i] = __rect_tilde_02_t;
                            }
                        
                            this->rect_tilde_02_lastSyncPhase = __rect_tilde_02_lastSyncPhase;
                            this->rect_tilde_02_lastSyncDiff = __rect_tilde_02_lastSyncDiff;
                            this->rect_tilde_02_t = __rect_tilde_02_t;
                            this->rect_tilde_02_didSync = __rect_tilde_02_didSync;
                            this->rect_tilde_02_yHistory = __rect_tilde_02_yHistory;
                            this->rect_tilde_02_xHistory = __rect_tilde_02_xHistory;
                        }
                        
                        void selector_02_perform(
                            number onoff,
                            const SampleValue * in1,
                            const SampleValue * in2,
                            const SampleValue * in3,
                            const SampleValue * in4,
                            const SampleValue * in5,
                            const SampleValue * in6,
                            SampleValue * out,
                            Index n
                        ) {
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                if (onoff >= 1 && onoff < 2)
                                    out[(Index)i] = in1[(Index)i];
                                else if (onoff >= 2 && onoff < 3)
                                    out[(Index)i] = in2[(Index)i];
                                else if (onoff >= 3 && onoff < 4)
                                    out[(Index)i] = in3[(Index)i];
                                else if (onoff >= 4 && onoff < 5)
                                    out[(Index)i] = in4[(Index)i];
                                else if (onoff >= 5 && onoff < 6)
                                    out[(Index)i] = in5[(Index)i];
                                else if (onoff >= 6 && onoff < 7)
                                    out[(Index)i] = in6[(Index)i];
                                else
                                    out[(Index)i] = 0;
                            }
                        }
                        
                        void ip_03_perform(SampleValue * out, Index n) {
                            auto __ip_03_lastValue = this->ip_03_lastValue;
                            auto __ip_03_lastIndex = this->ip_03_lastIndex;
                        
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = ((SampleIndex)(i) >= __ip_03_lastIndex ? __ip_03_lastValue : this->ip_03_sigbuf[(Index)i]);
                            }
                        
                            __ip_03_lastIndex = 0;
                            this->ip_03_lastIndex = __ip_03_lastIndex;
                        }
                        
                        void selector_03_perform(
                            number onoff,
                            const SampleValue * in1,
                            const SampleValue * in2,
                            const SampleValue * in3,
                            const SampleValue * in4,
                            const SampleValue * in5,
                            const SampleValue * in6,
                            SampleValue * out,
                            Index n
                        ) {
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                if (onoff >= 1 && onoff < 2)
                                    out[(Index)i] = in1[(Index)i];
                                else if (onoff >= 2 && onoff < 3)
                                    out[(Index)i] = in2[(Index)i];
                                else if (onoff >= 3 && onoff < 4)
                                    out[(Index)i] = in3[(Index)i];
                                else if (onoff >= 4 && onoff < 5)
                                    out[(Index)i] = in4[(Index)i];
                                else if (onoff >= 5 && onoff < 6)
                                    out[(Index)i] = in5[(Index)i];
                                else if (onoff >= 6 && onoff < 7)
                                    out[(Index)i] = in6[(Index)i];
                                else
                                    out[(Index)i] = 0;
                            }
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void numberobj_01_value_setter(number v) {
                            number localvalue = v;
                        
                            if (this->numberobj_01_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->numberobj_01_value = localvalue;
                        }
                        
                        void numberobj_01_init() {
                            this->numberobj_01_currentFormat = 6;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscB/number_obj-39"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->numberobj_01_value;
                        }
                        
                        void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->numberobj_01_value_set(preset["value"]);
                        }
                        
                        void param_08_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->param_08_value;
                        }
                        
                        void param_08_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->param_08_value_set(preset["value"]);
                        }
                        
                        void noise_tilde_01_init() {
                            this->noise_tilde_01_reset();
                        }
                        
                        void noise_tilde_01_reset() {
                            xoshiro_reset(
                                systemticks() + this->voice() + this->random(0, 10000),
                                this->noise_tilde_01_state
                            );
                        }
                        
                        number cycle_tilde_01_ph_next(number freq, number reset) {
                            {
                                {
                                    if (reset >= 0.)
                                        this->cycle_tilde_01_ph_currentPhase = reset;
                                }
                            }
                        
                            number pincr = freq * this->cycle_tilde_01_ph_conv;
                        
                            if (this->cycle_tilde_01_ph_currentPhase < 0.)
                                this->cycle_tilde_01_ph_currentPhase = 1. + this->cycle_tilde_01_ph_currentPhase;
                        
                            if (this->cycle_tilde_01_ph_currentPhase > 1.)
                                this->cycle_tilde_01_ph_currentPhase = this->cycle_tilde_01_ph_currentPhase - 1.;
                        
                            number tmp = this->cycle_tilde_01_ph_currentPhase;
                            this->cycle_tilde_01_ph_currentPhase += pincr;
                            return tmp;
                        }
                        
                        void cycle_tilde_01_ph_reset() {
                            this->cycle_tilde_01_ph_currentPhase = 0;
                        }
                        
                        void cycle_tilde_01_ph_dspsetup() {
                            this->cycle_tilde_01_ph_conv = (number)1 / this->sr;
                        }
                        
                        void cycle_tilde_01_dspsetup(bool force) {
                            if ((bool)(this->cycle_tilde_01_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->cycle_tilde_01_phasei = 0;
                            this->cycle_tilde_01_f2i = (number)4294967296 / this->samplerate();
                            this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
                            this->cycle_tilde_01_setupDone = true;
                            this->cycle_tilde_01_ph_dspsetup();
                        }
                        
                        void cycle_tilde_01_bufferUpdated() {
                            this->cycle_tilde_01_wrap = (long)(this->cycle_tilde_01_buffer->getSize()) - 1;
                        }
                        
                        number numbertilde_01_smooth_d_next(number x) {
                            number temp = (number)(x - this->numbertilde_01_smooth_d_prev);
                            this->numbertilde_01_smooth_d_prev = x;
                            return temp;
                        }
                        
                        void numbertilde_01_smooth_d_dspsetup() {
                            this->numbertilde_01_smooth_d_reset();
                        }
                        
                        void numbertilde_01_smooth_d_reset() {
                            this->numbertilde_01_smooth_d_prev = 0;
                        }
                        
                        number numbertilde_01_smooth_next(number x, number up, number down) {
                            if (this->numbertilde_01_smooth_d_next(x) != 0.) {
                                if (x > this->numbertilde_01_smooth_prev) {
                                    number _up = up;
                        
                                    if (_up < 1)
                                        _up = 1;
                        
                                    this->numbertilde_01_smooth_index = _up;
                                    this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _up;
                                } else if (x < this->numbertilde_01_smooth_prev) {
                                    number _down = down;
                        
                                    if (_down < 1)
                                        _down = 1;
                        
                                    this->numbertilde_01_smooth_index = _down;
                                    this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _down;
                                }
                            }
                        
                            if (this->numbertilde_01_smooth_index > 0) {
                                this->numbertilde_01_smooth_prev += this->numbertilde_01_smooth_increment;
                                this->numbertilde_01_smooth_index -= 1;
                            } else {
                                this->numbertilde_01_smooth_prev = x;
                            }
                        
                            return this->numbertilde_01_smooth_prev;
                        }
                        
                        void numbertilde_01_smooth_reset() {
                            this->numbertilde_01_smooth_prev = 0;
                            this->numbertilde_01_smooth_index = 0;
                            this->numbertilde_01_smooth_increment = 0;
                            this->numbertilde_01_smooth_d_reset();
                        }
                        
                        void numbertilde_01_init() {
                            this->numbertilde_01_currentMode = 0;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscB/number~_obj-18"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numbertilde_01_dspsetup(bool force) {
                            if ((bool)(this->numbertilde_01_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->numbertilde_01_currentIntervalInSamples = this->mstosamps(100);
                            this->numbertilde_01_currentInterval = this->numbertilde_01_currentIntervalInSamples;
                            this->numbertilde_01_rampInSamples = this->mstosamps(this->numbertilde_01_ramp);
                            this->numbertilde_01_setupDone = true;
                            this->numbertilde_01_smooth_d_dspsetup();
                        }
                        
                        number saw_tilde_01_dcblocker_next(number x, number gain) {
                            number y = x - this->saw_tilde_01_dcblocker_xm1 + this->saw_tilde_01_dcblocker_ym1 * gain;
                            this->saw_tilde_01_dcblocker_xm1 = x;
                            this->saw_tilde_01_dcblocker_ym1 = y;
                            return y;
                        }
                        
                        void saw_tilde_01_dcblocker_reset() {
                            this->saw_tilde_01_dcblocker_xm1 = 0;
                            this->saw_tilde_01_dcblocker_ym1 = 0;
                        }
                        
                        void saw_tilde_01_dcblocker_dspsetup() {
                            this->saw_tilde_01_dcblocker_reset();
                        }
                        
                        void saw_tilde_01_dspsetup(bool force) {
                            if ((bool)(this->saw_tilde_01_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->saw_tilde_01_setupDone = true;
                            this->saw_tilde_01_dcblocker_dspsetup();
                        }
                        
                        number numbertilde_02_smooth_d_next(number x) {
                            number temp = (number)(x - this->numbertilde_02_smooth_d_prev);
                            this->numbertilde_02_smooth_d_prev = x;
                            return temp;
                        }
                        
                        void numbertilde_02_smooth_d_dspsetup() {
                            this->numbertilde_02_smooth_d_reset();
                        }
                        
                        void numbertilde_02_smooth_d_reset() {
                            this->numbertilde_02_smooth_d_prev = 0;
                        }
                        
                        number numbertilde_02_smooth_next(number x, number up, number down) {
                            if (this->numbertilde_02_smooth_d_next(x) != 0.) {
                                if (x > this->numbertilde_02_smooth_prev) {
                                    number _up = up;
                        
                                    if (_up < 1)
                                        _up = 1;
                        
                                    this->numbertilde_02_smooth_index = _up;
                                    this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _up;
                                } else if (x < this->numbertilde_02_smooth_prev) {
                                    number _down = down;
                        
                                    if (_down < 1)
                                        _down = 1;
                        
                                    this->numbertilde_02_smooth_index = _down;
                                    this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _down;
                                }
                            }
                        
                            if (this->numbertilde_02_smooth_index > 0) {
                                this->numbertilde_02_smooth_prev += this->numbertilde_02_smooth_increment;
                                this->numbertilde_02_smooth_index -= 1;
                            } else {
                                this->numbertilde_02_smooth_prev = x;
                            }
                        
                            return this->numbertilde_02_smooth_prev;
                        }
                        
                        void numbertilde_02_smooth_reset() {
                            this->numbertilde_02_smooth_prev = 0;
                            this->numbertilde_02_smooth_index = 0;
                            this->numbertilde_02_smooth_increment = 0;
                            this->numbertilde_02_smooth_d_reset();
                        }
                        
                        void numbertilde_02_init() {
                            this->numbertilde_02_currentMode = 0;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscB/number~_obj-25"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numbertilde_02_dspsetup(bool force) {
                            if ((bool)(this->numbertilde_02_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->numbertilde_02_currentIntervalInSamples = this->mstosamps(100);
                            this->numbertilde_02_currentInterval = this->numbertilde_02_currentIntervalInSamples;
                            this->numbertilde_02_rampInSamples = this->mstosamps(this->numbertilde_02_ramp);
                            this->numbertilde_02_setupDone = true;
                            this->numbertilde_02_smooth_d_dspsetup();
                        }
                        
                        number tri_tilde_01_dcblocker_next(number x, number gain) {
                            number y = x - this->tri_tilde_01_dcblocker_xm1 + this->tri_tilde_01_dcblocker_ym1 * gain;
                            this->tri_tilde_01_dcblocker_xm1 = x;
                            this->tri_tilde_01_dcblocker_ym1 = y;
                            return y;
                        }
                        
                        void tri_tilde_01_dcblocker_reset() {
                            this->tri_tilde_01_dcblocker_xm1 = 0;
                            this->tri_tilde_01_dcblocker_ym1 = 0;
                        }
                        
                        void tri_tilde_01_dcblocker_dspsetup() {
                            this->tri_tilde_01_dcblocker_reset();
                        }
                        
                        void tri_tilde_01_dspsetup(bool force) {
                            if ((bool)(this->tri_tilde_01_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->tri_tilde_01_setupDone = true;
                            this->tri_tilde_01_dcblocker_dspsetup();
                        }
                        
                        void ip_03_init() {
                            this->ip_03_lastValue = this->ip_03_value;
                        }
                        
                        void ip_03_dspsetup(bool force) {
                            if ((bool)(this->ip_03_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->ip_03_lastIndex = 0;
                            this->ip_03_setupDone = true;
                        }
                        
                        number rect_tilde_01_rectangle(number phase, number pulsewidth) {
                            if (phase < pulsewidth) {
                                return 1;
                            } else {
                                return -1;
                            }
                        }
                        
                        number rect_tilde_02_rectangle(number phase, number pulsewidth) {
                            if (phase < pulsewidth) {
                                return 1;
                            } else {
                                return -1;
                            }
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            numberobj_01_value = 0;
                            numberobj_01_value_setter(numberobj_01_value);
                            expr_02_in1 = 0;
                            expr_02_in2 = 1;
                            expr_02_out1 = 0;
                            selector_02_onoff = 1;
                            param_08_value = 2;
                            cycle_tilde_01_frequency = 0;
                            cycle_tilde_01_phase_offset = 0;
                            numbertilde_01_input_number = 0;
                            numbertilde_01_ramp = 0;
                            saw_tilde_01_frequency = 0;
                            saw_tilde_01_syncPhase = 0;
                            numbertilde_02_input_number = 0;
                            numbertilde_02_ramp = 0;
                            tri_tilde_01_frequency = 0;
                            tri_tilde_01_pulsewidth = 0.5;
                            tri_tilde_01_syncPhase = 0;
                            selector_03_onoff = 1;
                            ip_03_value = 0;
                            ip_03_impulse = 0;
                            rect_tilde_01_frequency = 440;
                            rect_tilde_01_pulsewidth = 0.5;
                            rect_tilde_01_syncPhase = 0;
                            rect_tilde_02_frequency = 0;
                            rect_tilde_02_pulsewidth = 0.5;
                            rect_tilde_02_syncPhase = 0;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            signals[1] = nullptr;
                            signals[2] = nullptr;
                            signals[3] = nullptr;
                            signals[4] = nullptr;
                            signals[5] = nullptr;
                            signals[6] = nullptr;
                            signals[7] = nullptr;
                            signals[8] = nullptr;
                            signals[9] = nullptr;
                            signals[10] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            numberobj_01_currentFormat = 6;
                            numberobj_01_lastValue = 0;
                            param_08_lastValue = 0;
                            cycle_tilde_01_wrap = 0;
                            cycle_tilde_01_ph_currentPhase = 0;
                            cycle_tilde_01_ph_conv = 0;
                            cycle_tilde_01_setupDone = false;
                            numbertilde_01_currentInterval = 0;
                            numbertilde_01_currentIntervalInSamples = 0;
                            numbertilde_01_lastValue = 0;
                            numbertilde_01_outValue = 0;
                            numbertilde_01_rampInSamples = 0;
                            numbertilde_01_currentMode = 0;
                            numbertilde_01_smooth_d_prev = 0;
                            numbertilde_01_smooth_prev = 0;
                            numbertilde_01_smooth_index = 0;
                            numbertilde_01_smooth_increment = 0;
                            numbertilde_01_setupDone = false;
                            saw_tilde_01_t = 0;
                            saw_tilde_01_lastSyncPhase = 0;
                            saw_tilde_01_lastSyncDiff = 0;
                            saw_tilde_01_didSync = false;
                            saw_tilde_01_dcblocker_xm1 = 0;
                            saw_tilde_01_dcblocker_ym1 = 0;
                            saw_tilde_01_setupDone = false;
                            numbertilde_02_currentInterval = 0;
                            numbertilde_02_currentIntervalInSamples = 0;
                            numbertilde_02_lastValue = 0;
                            numbertilde_02_outValue = 0;
                            numbertilde_02_rampInSamples = 0;
                            numbertilde_02_currentMode = 0;
                            numbertilde_02_smooth_d_prev = 0;
                            numbertilde_02_smooth_prev = 0;
                            numbertilde_02_smooth_index = 0;
                            numbertilde_02_smooth_increment = 0;
                            numbertilde_02_setupDone = false;
                            tri_tilde_01_t = 0;
                            tri_tilde_01_lastSyncPhase = 0;
                            tri_tilde_01_lastSyncDiff = 0;
                            tri_tilde_01_didSync = false;
                            tri_tilde_01_yn = 0;
                            tri_tilde_01_yn1 = 0;
                            tri_tilde_01_yn2 = 0;
                            tri_tilde_01_yn3 = 0;
                            tri_tilde_01_flg = 0;
                            tri_tilde_01_app_correction = 0;
                            tri_tilde_01_dcblocker_xm1 = 0;
                            tri_tilde_01_dcblocker_ym1 = 0;
                            tri_tilde_01_setupDone = false;
                            ip_03_lastIndex = 0;
                            ip_03_lastValue = 0;
                            ip_03_resetCount = 0;
                            ip_03_sigbuf = nullptr;
                            ip_03_setupDone = false;
                            rect_tilde_01_xHistory = 0;
                            rect_tilde_01_yHistory = 0;
                            rect_tilde_01_t = 0;
                            rect_tilde_01_lastSyncPhase = 0;
                            rect_tilde_01_lastSyncDiff = 0;
                            rect_tilde_01_didSync = false;
                            rect_tilde_02_xHistory = 0;
                            rect_tilde_02_yHistory = 0;
                            rect_tilde_02_t = 0;
                            rect_tilde_02_lastSyncPhase = 0;
                            rect_tilde_02_lastSyncDiff = 0;
                            rect_tilde_02_didSync = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number numberobj_01_value;
                            number expr_02_in1;
                            number expr_02_in2;
                            number expr_02_out1;
                            number selector_02_onoff;
                            number param_08_value;
                            number cycle_tilde_01_frequency;
                            number cycle_tilde_01_phase_offset;
                            number numbertilde_01_input_number;
                            number numbertilde_01_ramp;
                            number saw_tilde_01_frequency;
                            number saw_tilde_01_syncPhase;
                            number numbertilde_02_input_number;
                            number numbertilde_02_ramp;
                            number tri_tilde_01_frequency;
                            number tri_tilde_01_pulsewidth;
                            number tri_tilde_01_syncPhase;
                            number selector_03_onoff;
                            number ip_03_value;
                            number ip_03_impulse;
                            number rect_tilde_01_frequency;
                            number rect_tilde_01_pulsewidth;
                            number rect_tilde_01_syncPhase;
                            number rect_tilde_02_frequency;
                            number rect_tilde_02_pulsewidth;
                            number rect_tilde_02_syncPhase;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[11];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            Int numberobj_01_currentFormat;
                            number numberobj_01_lastValue;
                            number param_08_lastValue;
                            UInt noise_tilde_01_state[4] = { };
                            Float64BufferRef cycle_tilde_01_buffer;
                            long cycle_tilde_01_wrap;
                            uint32_t cycle_tilde_01_phasei;
                            SampleValue cycle_tilde_01_f2i;
                            number cycle_tilde_01_ph_currentPhase;
                            number cycle_tilde_01_ph_conv;
                            bool cycle_tilde_01_setupDone;
                            SampleIndex numbertilde_01_currentInterval;
                            SampleIndex numbertilde_01_currentIntervalInSamples;
                            number numbertilde_01_lastValue;
                            number numbertilde_01_outValue;
                            number numbertilde_01_rampInSamples;
                            Int numbertilde_01_currentMode;
                            number numbertilde_01_smooth_d_prev;
                            number numbertilde_01_smooth_prev;
                            number numbertilde_01_smooth_index;
                            number numbertilde_01_smooth_increment;
                            bool numbertilde_01_setupDone;
                            number saw_tilde_01_t;
                            number saw_tilde_01_lastSyncPhase;
                            number saw_tilde_01_lastSyncDiff;
                            bool saw_tilde_01_didSync;
                            number saw_tilde_01_dcblocker_xm1;
                            number saw_tilde_01_dcblocker_ym1;
                            bool saw_tilde_01_setupDone;
                            SampleIndex numbertilde_02_currentInterval;
                            SampleIndex numbertilde_02_currentIntervalInSamples;
                            number numbertilde_02_lastValue;
                            number numbertilde_02_outValue;
                            number numbertilde_02_rampInSamples;
                            Int numbertilde_02_currentMode;
                            number numbertilde_02_smooth_d_prev;
                            number numbertilde_02_smooth_prev;
                            number numbertilde_02_smooth_index;
                            number numbertilde_02_smooth_increment;
                            bool numbertilde_02_setupDone;
                            number tri_tilde_01_t;
                            number tri_tilde_01_lastSyncPhase;
                            number tri_tilde_01_lastSyncDiff;
                            bool tri_tilde_01_didSync;
                            number tri_tilde_01_yn;
                            number tri_tilde_01_yn1;
                            number tri_tilde_01_yn2;
                            number tri_tilde_01_yn3;
                            number tri_tilde_01_flg;
                            number tri_tilde_01_app_correction;
                            number tri_tilde_01_dcblocker_xm1;
                            number tri_tilde_01_dcblocker_ym1;
                            bool tri_tilde_01_setupDone;
                            SampleIndex ip_03_lastIndex;
                            number ip_03_lastValue;
                            SampleIndex ip_03_resetCount;
                            signal ip_03_sigbuf;
                            bool ip_03_setupDone;
                            number rect_tilde_01_xHistory;
                            number rect_tilde_01_yHistory;
                            number rect_tilde_01_t;
                            number rect_tilde_01_lastSyncPhase;
                            number rect_tilde_01_lastSyncDiff;
                            bool rect_tilde_01_didSync;
                            number rect_tilde_02_xHistory;
                            number rect_tilde_02_yHistory;
                            number rect_tilde_02_t;
                            number rect_tilde_02_lastSyncPhase;
                            number rect_tilde_02_lastSyncDiff;
                            bool rect_tilde_02_didSync;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_62 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_66;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_62()
                        {
                        }
                        
                        ~RNBOSubpatcher_62()
                        {
                        }
                        
                        virtual RNBOSubpatcher_66* getPatcher() const {
                            return static_cast<RNBOSubpatcher_66 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                            getEngine()->flushClockEvents(this, 2098551528, false);
                            getEngine()->flushClockEvents(this, -1494586265, false);
                        }
                        
                        Index voice() {
                            return this->_voiceIndex;
                        }
                        
                        number random(number low, number high) {
                            number range = high - low;
                            return globalrandom() * range + low;
                        }
                        
                        number samplerate() const {
                            return this->sr;
                        }
                        
                        number mstosamps(MillisecondTime ms) {
                            return ms * this->sr * 0.001;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                            SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                            const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                            const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                            this->noise_tilde_02_perform(this->signals[0], n);
                        
                            this->cycle_tilde_02_perform(
                                in1,
                                this->cycle_tilde_02_phase_offset,
                                this->signals[1],
                                this->signals[2],
                                n
                            );
                        
                            this->numbertilde_03_perform(in1, this->dummyBuffer, n);
                            this->saw_tilde_02_perform(in1, this->saw_tilde_02_syncPhase, this->signals[3], this->signals[4], n);
                        
                            this->rect_tilde_03_perform(
                                in1,
                                in2,
                                this->rect_tilde_03_syncPhase,
                                this->signals[5],
                                this->signals[6],
                                n
                            );
                        
                            this->tri_tilde_02_perform(
                                in1,
                                in2,
                                this->tri_tilde_02_syncPhase,
                                this->signals[7],
                                this->signals[8],
                                n
                            );
                        
                            this->numbertilde_04_perform(in2, this->dummyBuffer, n);
                        
                            this->rect_tilde_04_perform(
                                in1,
                                in2,
                                this->rect_tilde_04_syncPhase,
                                this->signals[9],
                                this->signals[10],
                                n
                            );
                        
                            this->selector_04_perform(
                                this->selector_04_onoff,
                                this->signals[0],
                                this->signals[1],
                                this->signals[3],
                                this->signals[7],
                                this->signals[5],
                                this->signals[9],
                                out1,
                                n
                            );
                        
                            this->ip_04_perform(this->signals[9], n);
                        
                            this->selector_05_perform(
                                this->selector_05_onoff,
                                this->signals[9],
                                this->signals[2],
                                this->signals[4],
                                this->signals[8],
                                this->signals[6],
                                this->signals[10],
                                out2,
                                n
                            );
                        
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 11; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->ip_04_sigbuf = resizeSignal(this->ip_04_sigbuf, this->maxvs, maxBlockSize);
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            this->cycle_tilde_02_dspsetup(forceDSPSetup);
                            this->numbertilde_03_dspsetup(forceDSPSetup);
                            this->saw_tilde_02_dspsetup(forceDSPSetup);
                            this->tri_tilde_02_dspsetup(forceDSPSetup);
                            this->numbertilde_04_dspsetup(forceDSPSetup);
                            this->ip_04_dspsetup(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& preset) {
                            this->param_09_getPresetValue(getSubState(preset, "mode"));
                        }
                        
                        void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                            this->updateTime(time);
                        
                            switch (index) {
                            case 0:
                                {
                                this->param_09_value_set(v);
                                break;
                                }
                            }
                        }
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            case 0:
                                {
                                return this->param_09_value;
                                }
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 1;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            case 0:
                                {
                                return "mode";
                                }
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            case 0:
                                {
                                return "poly/oscillators/oscA/mode";
                                }
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                            {
                                switch (index) {
                                case 0:
                                    {
                                    info->type = ParameterTypeNumber;
                                    info->initialValue = 2;
                                    info->min = 0;
                                    info->max = 5;
                                    info->exponent = 1;
                                    info->steps = 6;
                                    static const char * eVal0[] = {"noise", "sine", "saw", "triangle", "square", "pulse"};
                                    info->enumValues = eVal0;
                                    info->debug = false;
                                    info->saveable = true;
                                    info->transmittable = true;
                                    info->initialized = true;
                                    info->visible = true;
                                    info->displayName = "";
                                    info->unit = "";
                                    info->ioType = IOTypeUndefined;
                                    info->signalIndex = INVALID_INDEX;
                                    break;
                                    }
                                }
                            }
                        }
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            case 0:
                                {
                                {
                                    value = (value < 0 ? 0 : (value > 5 ? 5 : value));
                                    ParameterValue normalizedValue = (value - 0) / (5 - 0);
                        
                                    {
                                        normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 6);
                                    }
                        
                                    return normalizedValue;
                                }
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            case 0:
                                {
                                {
                                    {
                                        value = this->applyStepsToNormalizedParameterValue(value, 6);
                                    }
                        
                                    {
                                        return 0 + value * (5 - 0);
                                    }
                                }
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            case 0:
                                {
                                return this->param_09_value_constrain(value);
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                            RNBO_UNUSED(hasValue);
                            this->updateTime(time);
                        
                            switch (index) {
                            case 2098551528:
                                {
                                this->numbertilde_03_value_set(value);
                                break;
                                }
                            case -1494586265:
                                {
                                this->numbertilde_04_value_set(value);
                                break;
                                }
                            }
                        }
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("valin"):
                                {
                                if (TAG("poly/oscillators/oscA/number_obj-39") == objectId)
                                    this->numberobj_02_valin_set(payload);
                        
                                break;
                                }
                            case TAG("format"):
                                {
                                if (TAG("poly/oscillators/oscA/number_obj-39") == objectId)
                                    this->numberobj_02_format_set(payload);
                        
                                break;
                                }
                            case TAG("sig"):
                                {
                                if (TAG("poly/oscillators/oscA/number~_obj-18") == objectId)
                                    this->numbertilde_03_sig_number_set(payload);
                        
                                if (TAG("poly/oscillators/oscA/number~_obj-25") == objectId)
                                    this->numbertilde_04_sig_number_set(payload);
                        
                                break;
                                }
                            case TAG("mode"):
                                {
                                if (TAG("poly/oscillators/oscA/number~_obj-18") == objectId)
                                    this->numbertilde_03_mode_set(payload);
                        
                                if (TAG("poly/oscillators/oscA/number~_obj-25") == objectId)
                                    this->numbertilde_04_mode_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processListMessage(
                            MessageTag tag,
                            MessageTag objectId,
                            MillisecondTime time,
                            const list& payload
                        ) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("sig"):
                                {
                                if (TAG("poly/oscillators/oscA/number~_obj-18") == objectId)
                                    this->numbertilde_03_sig_list_set(payload);
                        
                                if (TAG("poly/oscillators/oscA/number~_obj-25") == objectId)
                                    this->numbertilde_04_sig_list_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                            case TAG("valout"):
                                {
                                return "valout";
                                }
                            case TAG("poly/oscillators/oscA/number_obj-39"):
                                {
                                return "poly/oscillators/oscA/number_obj-39";
                                }
                            case TAG("setup"):
                                {
                                return "setup";
                                }
                            case TAG("monitor"):
                                {
                                return "monitor";
                                }
                            case TAG("poly/oscillators/oscA/number~_obj-18"):
                                {
                                return "poly/oscillators/oscA/number~_obj-18";
                                }
                            case TAG("assign"):
                                {
                                return "assign";
                                }
                            case TAG("poly/oscillators/oscA/number~_obj-25"):
                                {
                                return "poly/oscillators/oscA/number~_obj-25";
                                }
                            case TAG("valin"):
                                {
                                return "valin";
                                }
                            case TAG("format"):
                                {
                                return "format";
                                }
                            case TAG("sig"):
                                {
                                return "sig";
                                }
                            case TAG("mode"):
                                {
                                return "mode";
                                }
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                            this->updateTime(time);
                        
                            if (index == 1) {
                                this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                                this->cycle_tilde_02_bufferUpdated();
                            }
                        }
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                            this->cycle_tilde_02_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                        }
                        
                        protected:
                        
                        void param_09_value_set(number v) {
                            v = this->param_09_value_constrain(v);
                            this->param_09_value = v;
                            this->sendParameter(0, false);
                        
                            if (this->param_09_value != this->param_09_lastValue) {
                                this->getEngine()->presetTouched();
                                this->param_09_lastValue = this->param_09_value;
                            }
                        
                            this->expr_03_in1_set(v);
                            this->numberobj_02_value_set(v);
                        }
                        
                        void numberobj_02_valin_set(number v) {
                            this->numberobj_02_value_set(v);
                        }
                        
                        void numberobj_02_format_set(number v) {
                            this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
                        }
                        
                        void numbertilde_03_sig_number_set(number v) {
                            this->numbertilde_03_outValue = v;
                        }
                        
                        void numbertilde_03_sig_list_set(const list& v) {
                            this->numbertilde_03_outValue = v[0];
                        }
                        
                        void numbertilde_03_mode_set(number v) {
                            if (v == 1) {
                                this->numbertilde_03_currentMode = 0;
                            } else if (v == 2) {
                                this->numbertilde_03_currentMode = 1;
                            }
                        }
                        
                        void numbertilde_04_sig_number_set(number v) {
                            this->numbertilde_04_outValue = v;
                        }
                        
                        void numbertilde_04_sig_list_set(const list& v) {
                            this->numbertilde_04_outValue = v[0];
                        }
                        
                        void numbertilde_04_mode_set(number v) {
                            if (v == 1) {
                                this->numbertilde_04_currentMode = 0;
                            } else if (v == 2) {
                                this->numbertilde_04_currentMode = 1;
                            }
                        }
                        
                        void numbertilde_03_value_set(number ) {}
                        
                        void numbertilde_04_value_set(number ) {}
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 2;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 2;
                        }
                        
                        void initializeObjects() {
                            this->numberobj_02_init();
                            this->noise_tilde_02_init();
                            this->numbertilde_03_init();
                            this->numbertilde_04_init();
                            this->ip_04_init();
                        }
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {
                            this->updateTime(this->getEngine()->getCurrentTime());
                        
                            {
                                this->scheduleParamInit(0, 0);
                            }
                        }
                        
                        void allocateDataRefs() {
                            this->cycle_tilde_02_buffer->requestSize(16384, 1);
                            this->cycle_tilde_02_buffer->setSampleRate(this->sr);
                            this->cycle_tilde_02_buffer = this->cycle_tilde_02_buffer->allocateIfNeeded();
                        }
                        
                        number param_09_value_constrain(number v) const {
                            v = (v > 5 ? 5 : (v < 0 ? 0 : v));
                        
                            {
                                number oneStep = (number)5 / (number)5;
                                number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
                                number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
                                v = numberOfSteps * oneStep;
                            }
                        
                            return v;
                        }
                        
                        void selector_05_onoff_set(number v) {
                            this->selector_05_onoff = v;
                        }
                        
                        void selector_04_onoff_set(number v) {
                            this->selector_04_onoff = v;
                        }
                        
                        void expr_03_out1_set(number v) {
                            this->expr_03_out1 = v;
                            this->selector_05_onoff_set(this->expr_03_out1);
                            this->selector_04_onoff_set(this->expr_03_out1);
                        }
                        
                        void expr_03_in1_set(number in1) {
                            this->expr_03_in1 = in1;
                            this->expr_03_out1_set(this->expr_03_in1 + this->expr_03_in2);//#map:oscillators/oscA/+_obj-7:1
                        }
                        
                        void numberobj_02_output_set(number ) {}
                        
                        void numberobj_02_value_set(number v) {
                            this->numberobj_02_value_setter(v);
                            v = this->numberobj_02_value;
                            number localvalue = v;
                        
                            if (this->numberobj_02_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->getEngine()->sendNumMessage(
                                TAG("valout"),
                                TAG("poly/oscillators/oscA/number_obj-39"),
                                localvalue,
                                this->_currentTime
                            );
                        
                            this->numberobj_02_output_set(localvalue);
                        }
                        
                        void noise_tilde_02_perform(SampleValue * out1, Index n) {
                            auto __noise_tilde_02_state = this->noise_tilde_02_state;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                out1[(Index)i] = xoshiro_next(__noise_tilde_02_state);
                            }
                        }
                        
                        void cycle_tilde_02_perform(
                            const Sample * frequency,
                            number phase_offset,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(phase_offset);
                            auto __cycle_tilde_02_f2i = this->cycle_tilde_02_f2i;
                            auto __cycle_tilde_02_buffer = this->cycle_tilde_02_buffer;
                            auto __cycle_tilde_02_phasei = this->cycle_tilde_02_phasei;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                {
                                    uint32_t uint_phase;
                        
                                    {
                                        {
                                            uint_phase = __cycle_tilde_02_phasei;
                                        }
                                    }
                        
                                    uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                                    number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                                    number y0 = __cycle_tilde_02_buffer[(Index)idx];
                                    number y1 = __cycle_tilde_02_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                                    number y = y0 + frac * (y1 - y0);
                        
                                    {
                                        uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_02_f2i));
                                        __cycle_tilde_02_phasei = uint32_add(__cycle_tilde_02_phasei, pincr);
                                    }
                        
                                    out1[(Index)i] = y;
                                    out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                                    continue;
                                }
                            }
                        
                            this->cycle_tilde_02_phasei = __cycle_tilde_02_phasei;
                        }
                        
                        void numbertilde_03_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
                            auto __numbertilde_03_currentIntervalInSamples = this->numbertilde_03_currentIntervalInSamples;
                            auto __numbertilde_03_lastValue = this->numbertilde_03_lastValue;
                            auto __numbertilde_03_currentInterval = this->numbertilde_03_currentInterval;
                            auto __numbertilde_03_rampInSamples = this->numbertilde_03_rampInSamples;
                            auto __numbertilde_03_outValue = this->numbertilde_03_outValue;
                            auto __numbertilde_03_currentMode = this->numbertilde_03_currentMode;
                            number monitorvalue = input_signal[0];
                        
                            for (Index i = 0; i < n; i++) {
                                if (__numbertilde_03_currentMode == 0) {
                                    output[(Index)i] = this->numbertilde_03_smooth_next(
                                        __numbertilde_03_outValue,
                                        __numbertilde_03_rampInSamples,
                                        __numbertilde_03_rampInSamples
                                    );
                                } else {
                                    output[(Index)i] = input_signal[(Index)i];
                                }
                            }
                        
                            __numbertilde_03_currentInterval -= n;
                        
                            if (monitorvalue != __numbertilde_03_lastValue && __numbertilde_03_currentInterval <= 0) {
                                __numbertilde_03_currentInterval = __numbertilde_03_currentIntervalInSamples;
                        
                                this->getEngine()->scheduleClockEventWithValue(
                                    this,
                                    2098551528,
                                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                                    monitorvalue
                                );;
                        
                                __numbertilde_03_lastValue = monitorvalue;
                        
                                this->getEngine()->sendListMessage(
                                    TAG("monitor"),
                                    TAG("poly/oscillators/oscA/number~_obj-18"),
                                    {monitorvalue},
                                    this->_currentTime
                                );;
                            }
                        
                            this->numbertilde_03_currentInterval = __numbertilde_03_currentInterval;
                            this->numbertilde_03_lastValue = __numbertilde_03_lastValue;
                        }
                        
                        void saw_tilde_02_perform(
                            const Sample * frequency,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __saw_tilde_02_didSync = this->saw_tilde_02_didSync;
                            auto __saw_tilde_02_lastSyncDiff = this->saw_tilde_02_lastSyncDiff;
                            auto __saw_tilde_02_lastSyncPhase = this->saw_tilde_02_lastSyncPhase;
                            auto __saw_tilde_02_t = this->saw_tilde_02_t;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number dt = frequency[(Index)i] / this->samplerate();
                                number t1 = __saw_tilde_02_t + 0.5;
                                t1 -= trunc(t1);
                                number y = 2 * t1 - 1;
                        
                                if (dt != 0.0) {
                                    number syncDiff = 0 - __saw_tilde_02_lastSyncPhase;
                                    __saw_tilde_02_lastSyncPhase = 0;
                                    __saw_tilde_02_lastSyncDiff = syncDiff;
                                    number lookahead = 0 + syncDiff;
                        
                                    if (t1 < dt) {
                                        number d = t1 / dt;
                                        y -= d + d - d * d - 1;
                                    } else if (t1 + dt > 1) {
                                        number d = (t1 - 1) / dt;
                                        y -= d + d + d * d + 1;
                                    } else if ((bool)(__saw_tilde_02_didSync)) {
                                        y = 0;
                                        __saw_tilde_02_didSync = false;
                                    } else if (lookahead > 1) {
                                        y *= 0.5;
                                        __saw_tilde_02_t = 0;
                                        __saw_tilde_02_didSync = true;
                                    }
                        
                                    __saw_tilde_02_t += dt;
                        
                                    if (dt > 0) {
                                        while (__saw_tilde_02_t >= 1) {
                                            __saw_tilde_02_t -= 1;
                                        }
                                    } else {
                                        while (__saw_tilde_02_t <= 0) {
                                            __saw_tilde_02_t += 1;
                                        }
                                    }
                                }
                        
                                y = this->saw_tilde_02_dcblocker_next(y, 0.9997);
                                out1[(Index)i] = 0.5 * y;
                                out2[(Index)i] = __saw_tilde_02_t;
                            }
                        
                            this->saw_tilde_02_t = __saw_tilde_02_t;
                            this->saw_tilde_02_lastSyncPhase = __saw_tilde_02_lastSyncPhase;
                            this->saw_tilde_02_lastSyncDiff = __saw_tilde_02_lastSyncDiff;
                            this->saw_tilde_02_didSync = __saw_tilde_02_didSync;
                        }
                        
                        void rect_tilde_03_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __rect_tilde_03_xHistory = this->rect_tilde_03_xHistory;
                            auto __rect_tilde_03_yHistory = this->rect_tilde_03_yHistory;
                            auto __rect_tilde_03_didSync = this->rect_tilde_03_didSync;
                            auto __rect_tilde_03_t = this->rect_tilde_03_t;
                            auto __rect_tilde_03_lastSyncDiff = this->rect_tilde_03_lastSyncDiff;
                            auto __rect_tilde_03_lastSyncPhase = this->rect_tilde_03_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                                number pw = pulsewidth[(Index)i];
                        
                                if (pulsewidth[(Index)i] > 0.99) {
                                    pw = 0.99;
                                } else if (pulsewidth[(Index)i] < 0.01) {
                                    pw = 0.01;
                                }
                        
                                number syncDiff = 0 - __rect_tilde_03_lastSyncPhase;
                                __rect_tilde_03_lastSyncPhase = 0;
                                __rect_tilde_03_lastSyncDiff = syncDiff;
                                number syncLookahead = 0 + syncDiff;
                                number tCurr = __rect_tilde_03_t;
                                number tPrev = tCurr - dt;
                                number tNext = tCurr + dt;
                        
                                if (tPrev < 0) {
                                    while (tPrev < 0) {
                                        tPrev += 1;
                                    }
                                }
                        
                                if (tNext > 1) {
                                    while (tNext >= 1) {
                                        tNext -= 1;
                                    }
                                }
                        
                                number yNext = this->rect_tilde_03_rectangle(tNext, pw);
                                number yCurr = this->rect_tilde_03_rectangle(tCurr, pw);
                                number yPrev = this->rect_tilde_03_rectangle(tPrev, pw);
                        
                                if (dt != 0.0) {
                                    if (yPrev < yCurr) {
                                        number d = tCurr / dt;
                                        yCurr += d - 0.5 * d * d - 0.5;
                                    } else if (yCurr < yNext) {
                                        number d = (1 - tCurr) / dt;
                                        yCurr += 0.5 * d * d + d + 0.5;
                                    } else if (yPrev > yCurr) {
                                        number d = (tCurr - pw) / dt;
                                        yCurr -= d - 0.5 * d * d - 0.5;
                                    } else if (yCurr > yNext) {
                                        number d = (pw - tCurr) / dt;
                                        yCurr -= 0.5 * d * d + d + 0.5;
                                    } else if ((bool)(__rect_tilde_03_didSync)) {
                                        yCurr = 0.25;
                                        __rect_tilde_03_didSync = false;
                                    } else if (syncLookahead > 1) {
                                        if (yCurr < 0) {
                                            yCurr = -0.125;
                                        }
                        
                                        __rect_tilde_03_t = 0;
                                        __rect_tilde_03_didSync = true;
                                    }
                        
                                    __rect_tilde_03_t += dt;
                        
                                    if (dt > 0) {
                                        while (__rect_tilde_03_t >= 1) {
                                            __rect_tilde_03_t -= 1;
                                        }
                                    } else {
                                        while (__rect_tilde_03_t <= 0) {
                                            __rect_tilde_03_t += 1;
                                        }
                                    }
                                }
                        
                                number output = yCurr - __rect_tilde_03_yHistory + __rect_tilde_03_xHistory * 0.9997;
                                __rect_tilde_03_xHistory = output;
                                __rect_tilde_03_yHistory = yCurr;
                                out1[(Index)i] = 0.5 * output;
                                out2[(Index)i] = __rect_tilde_03_t;
                            }
                        
                            this->rect_tilde_03_lastSyncPhase = __rect_tilde_03_lastSyncPhase;
                            this->rect_tilde_03_lastSyncDiff = __rect_tilde_03_lastSyncDiff;
                            this->rect_tilde_03_t = __rect_tilde_03_t;
                            this->rect_tilde_03_didSync = __rect_tilde_03_didSync;
                            this->rect_tilde_03_yHistory = __rect_tilde_03_yHistory;
                            this->rect_tilde_03_xHistory = __rect_tilde_03_xHistory;
                        }
                        
                        void tri_tilde_02_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __tri_tilde_02_yn3 = this->tri_tilde_02_yn3;
                            auto __tri_tilde_02_yn2 = this->tri_tilde_02_yn2;
                            auto __tri_tilde_02_yn1 = this->tri_tilde_02_yn1;
                            auto __tri_tilde_02_app_correction = this->tri_tilde_02_app_correction;
                            auto __tri_tilde_02_flg = this->tri_tilde_02_flg;
                            auto __tri_tilde_02_yn = this->tri_tilde_02_yn;
                            auto __tri_tilde_02_t = this->tri_tilde_02_t;
                            auto __tri_tilde_02_lastSyncDiff = this->tri_tilde_02_lastSyncDiff;
                            auto __tri_tilde_02_lastSyncPhase = this->tri_tilde_02_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                        
                                if (dt != 0.0) {
                                    number pw = pulsewidth[(Index)i];
                        
                                    if (pulsewidth[(Index)i] > 0.99) {
                                        pw = 0.99;
                                    } else if (pulsewidth[(Index)i] < 0.01) {
                                        pw = 0.01;
                                    }
                        
                                    number syncDiff = 0 - __tri_tilde_02_lastSyncPhase;
                                    __tri_tilde_02_lastSyncPhase = 0;
                                    __tri_tilde_02_lastSyncDiff = syncDiff;
                                    number syncLookahead = 0 + syncDiff;
                        
                                    if (syncLookahead > 1) {
                                        __tri_tilde_02_t = 0;
                                    }
                        
                                    number tCurr = __tri_tilde_02_t;
                                    number upSlope = __frequency / (pw * this->samplerate());
                                    number downSlope = __frequency / ((1 - pw) * this->samplerate());
                        
                                    if (tCurr <= pw) {
                                        __tri_tilde_02_yn = (number)2 / pw * tCurr - 1;
                        
                                        if (__tri_tilde_02_flg == -1) {
                                            __tri_tilde_02_app_correction = 1;
                                            __tri_tilde_02_flg = 1;
                                        } else if (__tri_tilde_02_app_correction == 1) {
                                            __tri_tilde_02_app_correction = 0;
                                            number d = (tCurr - dt) / dt;
                                            number d2 = d * d;
                                            number d3 = d2 * d;
                                            number d4 = d2 * d2;
                                            number d5 = d * d4;
                                            number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                            number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                            number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                            number h3 = d5 / (number)120;
                                            __tri_tilde_02_yn += upSlope * h0;
                                            __tri_tilde_02_yn1 += upSlope * h1;
                                            __tri_tilde_02_yn2 += upSlope * h2;
                                            __tri_tilde_02_yn3 += upSlope * h3;
                                        }
                        
                                        __tri_tilde_02_flg = 1;
                                    } else {
                                        __tri_tilde_02_yn = 1 - 2 * (tCurr - pw) / (1 - pw);
                        
                                        if (__tri_tilde_02_flg == 1) {
                                            __tri_tilde_02_app_correction = 1;
                                        } else if (__tri_tilde_02_app_correction == 1) {
                                            __tri_tilde_02_app_correction = 0;
                                            number d = (tCurr - pw - dt) / dt;
                                            number d2 = d * d;
                                            number d3 = d2 * d;
                                            number d4 = d2 * d2;
                                            number d5 = d4 * d;
                                            number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                            number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                            number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                            number h3 = d5 / (number)120;
                                            __tri_tilde_02_yn -= downSlope * h0;
                                            __tri_tilde_02_yn1 -= downSlope * h1;
                                            __tri_tilde_02_yn2 -= downSlope * h2;
                                            __tri_tilde_02_yn3 -= downSlope * h3;
                                        }
                        
                                        __tri_tilde_02_flg = -1;
                                    }
                                }
                        
                                number y = __tri_tilde_02_yn3;
                                __tri_tilde_02_yn3 = __tri_tilde_02_yn2;
                                __tri_tilde_02_yn2 = __tri_tilde_02_yn1;
                                __tri_tilde_02_yn1 = __tri_tilde_02_yn;
                                __tri_tilde_02_t += dt;
                        
                                if (dt > 0) {
                                    while (__tri_tilde_02_t >= 1) {
                                        __tri_tilde_02_t -= 1;
                                    }
                                } else {
                                    while (__tri_tilde_02_t <= 0) {
                                        __tri_tilde_02_t += 1;
                                    }
                                }
                        
                                y = this->tri_tilde_02_dcblocker_next(y, 0.9997);
                                out1[(Index)i] = y * 0.5;
                                out2[(Index)i] = __tri_tilde_02_t;
                            }
                        
                            this->tri_tilde_02_lastSyncPhase = __tri_tilde_02_lastSyncPhase;
                            this->tri_tilde_02_lastSyncDiff = __tri_tilde_02_lastSyncDiff;
                            this->tri_tilde_02_t = __tri_tilde_02_t;
                            this->tri_tilde_02_yn = __tri_tilde_02_yn;
                            this->tri_tilde_02_flg = __tri_tilde_02_flg;
                            this->tri_tilde_02_app_correction = __tri_tilde_02_app_correction;
                            this->tri_tilde_02_yn1 = __tri_tilde_02_yn1;
                            this->tri_tilde_02_yn2 = __tri_tilde_02_yn2;
                            this->tri_tilde_02_yn3 = __tri_tilde_02_yn3;
                        }
                        
                        void numbertilde_04_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
                            auto __numbertilde_04_currentIntervalInSamples = this->numbertilde_04_currentIntervalInSamples;
                            auto __numbertilde_04_lastValue = this->numbertilde_04_lastValue;
                            auto __numbertilde_04_currentInterval = this->numbertilde_04_currentInterval;
                            auto __numbertilde_04_rampInSamples = this->numbertilde_04_rampInSamples;
                            auto __numbertilde_04_outValue = this->numbertilde_04_outValue;
                            auto __numbertilde_04_currentMode = this->numbertilde_04_currentMode;
                            number monitorvalue = input_signal[0];
                        
                            for (Index i = 0; i < n; i++) {
                                if (__numbertilde_04_currentMode == 0) {
                                    output[(Index)i] = this->numbertilde_04_smooth_next(
                                        __numbertilde_04_outValue,
                                        __numbertilde_04_rampInSamples,
                                        __numbertilde_04_rampInSamples
                                    );
                                } else {
                                    output[(Index)i] = input_signal[(Index)i];
                                }
                            }
                        
                            __numbertilde_04_currentInterval -= n;
                        
                            if (monitorvalue != __numbertilde_04_lastValue && __numbertilde_04_currentInterval <= 0) {
                                __numbertilde_04_currentInterval = __numbertilde_04_currentIntervalInSamples;
                        
                                this->getEngine()->scheduleClockEventWithValue(
                                    this,
                                    -1494586265,
                                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                                    monitorvalue
                                );;
                        
                                __numbertilde_04_lastValue = monitorvalue;
                        
                                this->getEngine()->sendListMessage(
                                    TAG("monitor"),
                                    TAG("poly/oscillators/oscA/number~_obj-25"),
                                    {monitorvalue},
                                    this->_currentTime
                                );;
                            }
                        
                            this->numbertilde_04_currentInterval = __numbertilde_04_currentInterval;
                            this->numbertilde_04_lastValue = __numbertilde_04_lastValue;
                        }
                        
                        void rect_tilde_04_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __rect_tilde_04_xHistory = this->rect_tilde_04_xHistory;
                            auto __rect_tilde_04_yHistory = this->rect_tilde_04_yHistory;
                            auto __rect_tilde_04_didSync = this->rect_tilde_04_didSync;
                            auto __rect_tilde_04_t = this->rect_tilde_04_t;
                            auto __rect_tilde_04_lastSyncDiff = this->rect_tilde_04_lastSyncDiff;
                            auto __rect_tilde_04_lastSyncPhase = this->rect_tilde_04_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                                number pw = pulsewidth[(Index)i];
                        
                                if (pulsewidth[(Index)i] > 0.99) {
                                    pw = 0.99;
                                } else if (pulsewidth[(Index)i] < 0.01) {
                                    pw = 0.01;
                                }
                        
                                number syncDiff = 0 - __rect_tilde_04_lastSyncPhase;
                                __rect_tilde_04_lastSyncPhase = 0;
                                __rect_tilde_04_lastSyncDiff = syncDiff;
                                number syncLookahead = 0 + syncDiff;
                                number tCurr = __rect_tilde_04_t;
                                number tPrev = tCurr - dt;
                                number tNext = tCurr + dt;
                        
                                if (tPrev < 0) {
                                    while (tPrev < 0) {
                                        tPrev += 1;
                                    }
                                }
                        
                                if (tNext > 1) {
                                    while (tNext >= 1) {
                                        tNext -= 1;
                                    }
                                }
                        
                                number yNext = this->rect_tilde_04_rectangle(tNext, pw);
                                number yCurr = this->rect_tilde_04_rectangle(tCurr, pw);
                                number yPrev = this->rect_tilde_04_rectangle(tPrev, pw);
                        
                                if (dt != 0.0) {
                                    if (yPrev < yCurr) {
                                        number d = tCurr / dt;
                                        yCurr += d - 0.5 * d * d - 0.5;
                                    } else if (yCurr < yNext) {
                                        number d = (1 - tCurr) / dt;
                                        yCurr += 0.5 * d * d + d + 0.5;
                                    } else if (yPrev > yCurr) {
                                        number d = (tCurr - pw) / dt;
                                        yCurr -= d - 0.5 * d * d - 0.5;
                                    } else if (yCurr > yNext) {
                                        number d = (pw - tCurr) / dt;
                                        yCurr -= 0.5 * d * d + d + 0.5;
                                    } else if ((bool)(__rect_tilde_04_didSync)) {
                                        yCurr = 0.25;
                                        __rect_tilde_04_didSync = false;
                                    } else if (syncLookahead > 1) {
                                        if (yCurr < 0) {
                                            yCurr = -0.125;
                                        }
                        
                                        __rect_tilde_04_t = 0;
                                        __rect_tilde_04_didSync = true;
                                    }
                        
                                    __rect_tilde_04_t += dt;
                        
                                    if (dt > 0) {
                                        while (__rect_tilde_04_t >= 1) {
                                            __rect_tilde_04_t -= 1;
                                        }
                                    } else {
                                        while (__rect_tilde_04_t <= 0) {
                                            __rect_tilde_04_t += 1;
                                        }
                                    }
                                }
                        
                                number output = yCurr - __rect_tilde_04_yHistory + __rect_tilde_04_xHistory * 0.9997;
                                __rect_tilde_04_xHistory = output;
                                __rect_tilde_04_yHistory = yCurr;
                                out1[(Index)i] = 0.5 * output;
                                out2[(Index)i] = __rect_tilde_04_t;
                            }
                        
                            this->rect_tilde_04_lastSyncPhase = __rect_tilde_04_lastSyncPhase;
                            this->rect_tilde_04_lastSyncDiff = __rect_tilde_04_lastSyncDiff;
                            this->rect_tilde_04_t = __rect_tilde_04_t;
                            this->rect_tilde_04_didSync = __rect_tilde_04_didSync;
                            this->rect_tilde_04_yHistory = __rect_tilde_04_yHistory;
                            this->rect_tilde_04_xHistory = __rect_tilde_04_xHistory;
                        }
                        
                        void selector_04_perform(
                            number onoff,
                            const SampleValue * in1,
                            const SampleValue * in2,
                            const SampleValue * in3,
                            const SampleValue * in4,
                            const SampleValue * in5,
                            const SampleValue * in6,
                            SampleValue * out,
                            Index n
                        ) {
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                if (onoff >= 1 && onoff < 2)
                                    out[(Index)i] = in1[(Index)i];
                                else if (onoff >= 2 && onoff < 3)
                                    out[(Index)i] = in2[(Index)i];
                                else if (onoff >= 3 && onoff < 4)
                                    out[(Index)i] = in3[(Index)i];
                                else if (onoff >= 4 && onoff < 5)
                                    out[(Index)i] = in4[(Index)i];
                                else if (onoff >= 5 && onoff < 6)
                                    out[(Index)i] = in5[(Index)i];
                                else if (onoff >= 6 && onoff < 7)
                                    out[(Index)i] = in6[(Index)i];
                                else
                                    out[(Index)i] = 0;
                            }
                        }
                        
                        void ip_04_perform(SampleValue * out, Index n) {
                            auto __ip_04_lastValue = this->ip_04_lastValue;
                            auto __ip_04_lastIndex = this->ip_04_lastIndex;
                        
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = ((SampleIndex)(i) >= __ip_04_lastIndex ? __ip_04_lastValue : this->ip_04_sigbuf[(Index)i]);
                            }
                        
                            __ip_04_lastIndex = 0;
                            this->ip_04_lastIndex = __ip_04_lastIndex;
                        }
                        
                        void selector_05_perform(
                            number onoff,
                            const SampleValue * in1,
                            const SampleValue * in2,
                            const SampleValue * in3,
                            const SampleValue * in4,
                            const SampleValue * in5,
                            const SampleValue * in6,
                            SampleValue * out,
                            Index n
                        ) {
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                if (onoff >= 1 && onoff < 2)
                                    out[(Index)i] = in1[(Index)i];
                                else if (onoff >= 2 && onoff < 3)
                                    out[(Index)i] = in2[(Index)i];
                                else if (onoff >= 3 && onoff < 4)
                                    out[(Index)i] = in3[(Index)i];
                                else if (onoff >= 4 && onoff < 5)
                                    out[(Index)i] = in4[(Index)i];
                                else if (onoff >= 5 && onoff < 6)
                                    out[(Index)i] = in5[(Index)i];
                                else if (onoff >= 6 && onoff < 7)
                                    out[(Index)i] = in6[(Index)i];
                                else
                                    out[(Index)i] = 0;
                            }
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void numberobj_02_value_setter(number v) {
                            number localvalue = v;
                        
                            if (this->numberobj_02_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->numberobj_02_value = localvalue;
                        }
                        
                        void numberobj_02_init() {
                            this->numberobj_02_currentFormat = 6;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscA/number_obj-39"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->numberobj_02_value;
                        }
                        
                        void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->numberobj_02_value_set(preset["value"]);
                        }
                        
                        void param_09_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->param_09_value;
                        }
                        
                        void param_09_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->param_09_value_set(preset["value"]);
                        }
                        
                        void noise_tilde_02_init() {
                            this->noise_tilde_02_reset();
                        }
                        
                        void noise_tilde_02_reset() {
                            xoshiro_reset(
                                systemticks() + this->voice() + this->random(0, 10000),
                                this->noise_tilde_02_state
                            );
                        }
                        
                        number cycle_tilde_02_ph_next(number freq, number reset) {
                            {
                                {
                                    if (reset >= 0.)
                                        this->cycle_tilde_02_ph_currentPhase = reset;
                                }
                            }
                        
                            number pincr = freq * this->cycle_tilde_02_ph_conv;
                        
                            if (this->cycle_tilde_02_ph_currentPhase < 0.)
                                this->cycle_tilde_02_ph_currentPhase = 1. + this->cycle_tilde_02_ph_currentPhase;
                        
                            if (this->cycle_tilde_02_ph_currentPhase > 1.)
                                this->cycle_tilde_02_ph_currentPhase = this->cycle_tilde_02_ph_currentPhase - 1.;
                        
                            number tmp = this->cycle_tilde_02_ph_currentPhase;
                            this->cycle_tilde_02_ph_currentPhase += pincr;
                            return tmp;
                        }
                        
                        void cycle_tilde_02_ph_reset() {
                            this->cycle_tilde_02_ph_currentPhase = 0;
                        }
                        
                        void cycle_tilde_02_ph_dspsetup() {
                            this->cycle_tilde_02_ph_conv = (number)1 / this->sr;
                        }
                        
                        void cycle_tilde_02_dspsetup(bool force) {
                            if ((bool)(this->cycle_tilde_02_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->cycle_tilde_02_phasei = 0;
                            this->cycle_tilde_02_f2i = (number)4294967296 / this->samplerate();
                            this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
                            this->cycle_tilde_02_setupDone = true;
                            this->cycle_tilde_02_ph_dspsetup();
                        }
                        
                        void cycle_tilde_02_bufferUpdated() {
                            this->cycle_tilde_02_wrap = (long)(this->cycle_tilde_02_buffer->getSize()) - 1;
                        }
                        
                        number numbertilde_03_smooth_d_next(number x) {
                            number temp = (number)(x - this->numbertilde_03_smooth_d_prev);
                            this->numbertilde_03_smooth_d_prev = x;
                            return temp;
                        }
                        
                        void numbertilde_03_smooth_d_dspsetup() {
                            this->numbertilde_03_smooth_d_reset();
                        }
                        
                        void numbertilde_03_smooth_d_reset() {
                            this->numbertilde_03_smooth_d_prev = 0;
                        }
                        
                        number numbertilde_03_smooth_next(number x, number up, number down) {
                            if (this->numbertilde_03_smooth_d_next(x) != 0.) {
                                if (x > this->numbertilde_03_smooth_prev) {
                                    number _up = up;
                        
                                    if (_up < 1)
                                        _up = 1;
                        
                                    this->numbertilde_03_smooth_index = _up;
                                    this->numbertilde_03_smooth_increment = (x - this->numbertilde_03_smooth_prev) / _up;
                                } else if (x < this->numbertilde_03_smooth_prev) {
                                    number _down = down;
                        
                                    if (_down < 1)
                                        _down = 1;
                        
                                    this->numbertilde_03_smooth_index = _down;
                                    this->numbertilde_03_smooth_increment = (x - this->numbertilde_03_smooth_prev) / _down;
                                }
                            }
                        
                            if (this->numbertilde_03_smooth_index > 0) {
                                this->numbertilde_03_smooth_prev += this->numbertilde_03_smooth_increment;
                                this->numbertilde_03_smooth_index -= 1;
                            } else {
                                this->numbertilde_03_smooth_prev = x;
                            }
                        
                            return this->numbertilde_03_smooth_prev;
                        }
                        
                        void numbertilde_03_smooth_reset() {
                            this->numbertilde_03_smooth_prev = 0;
                            this->numbertilde_03_smooth_index = 0;
                            this->numbertilde_03_smooth_increment = 0;
                            this->numbertilde_03_smooth_d_reset();
                        }
                        
                        void numbertilde_03_init() {
                            this->numbertilde_03_currentMode = 0;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscA/number~_obj-18"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numbertilde_03_dspsetup(bool force) {
                            if ((bool)(this->numbertilde_03_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->numbertilde_03_currentIntervalInSamples = this->mstosamps(100);
                            this->numbertilde_03_currentInterval = this->numbertilde_03_currentIntervalInSamples;
                            this->numbertilde_03_rampInSamples = this->mstosamps(this->numbertilde_03_ramp);
                            this->numbertilde_03_setupDone = true;
                            this->numbertilde_03_smooth_d_dspsetup();
                        }
                        
                        number saw_tilde_02_dcblocker_next(number x, number gain) {
                            number y = x - this->saw_tilde_02_dcblocker_xm1 + this->saw_tilde_02_dcblocker_ym1 * gain;
                            this->saw_tilde_02_dcblocker_xm1 = x;
                            this->saw_tilde_02_dcblocker_ym1 = y;
                            return y;
                        }
                        
                        void saw_tilde_02_dcblocker_reset() {
                            this->saw_tilde_02_dcblocker_xm1 = 0;
                            this->saw_tilde_02_dcblocker_ym1 = 0;
                        }
                        
                        void saw_tilde_02_dcblocker_dspsetup() {
                            this->saw_tilde_02_dcblocker_reset();
                        }
                        
                        void saw_tilde_02_dspsetup(bool force) {
                            if ((bool)(this->saw_tilde_02_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->saw_tilde_02_setupDone = true;
                            this->saw_tilde_02_dcblocker_dspsetup();
                        }
                        
                        number numbertilde_04_smooth_d_next(number x) {
                            number temp = (number)(x - this->numbertilde_04_smooth_d_prev);
                            this->numbertilde_04_smooth_d_prev = x;
                            return temp;
                        }
                        
                        void numbertilde_04_smooth_d_dspsetup() {
                            this->numbertilde_04_smooth_d_reset();
                        }
                        
                        void numbertilde_04_smooth_d_reset() {
                            this->numbertilde_04_smooth_d_prev = 0;
                        }
                        
                        number numbertilde_04_smooth_next(number x, number up, number down) {
                            if (this->numbertilde_04_smooth_d_next(x) != 0.) {
                                if (x > this->numbertilde_04_smooth_prev) {
                                    number _up = up;
                        
                                    if (_up < 1)
                                        _up = 1;
                        
                                    this->numbertilde_04_smooth_index = _up;
                                    this->numbertilde_04_smooth_increment = (x - this->numbertilde_04_smooth_prev) / _up;
                                } else if (x < this->numbertilde_04_smooth_prev) {
                                    number _down = down;
                        
                                    if (_down < 1)
                                        _down = 1;
                        
                                    this->numbertilde_04_smooth_index = _down;
                                    this->numbertilde_04_smooth_increment = (x - this->numbertilde_04_smooth_prev) / _down;
                                }
                            }
                        
                            if (this->numbertilde_04_smooth_index > 0) {
                                this->numbertilde_04_smooth_prev += this->numbertilde_04_smooth_increment;
                                this->numbertilde_04_smooth_index -= 1;
                            } else {
                                this->numbertilde_04_smooth_prev = x;
                            }
                        
                            return this->numbertilde_04_smooth_prev;
                        }
                        
                        void numbertilde_04_smooth_reset() {
                            this->numbertilde_04_smooth_prev = 0;
                            this->numbertilde_04_smooth_index = 0;
                            this->numbertilde_04_smooth_increment = 0;
                            this->numbertilde_04_smooth_d_reset();
                        }
                        
                        void numbertilde_04_init() {
                            this->numbertilde_04_currentMode = 0;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscA/number~_obj-25"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numbertilde_04_dspsetup(bool force) {
                            if ((bool)(this->numbertilde_04_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->numbertilde_04_currentIntervalInSamples = this->mstosamps(100);
                            this->numbertilde_04_currentInterval = this->numbertilde_04_currentIntervalInSamples;
                            this->numbertilde_04_rampInSamples = this->mstosamps(this->numbertilde_04_ramp);
                            this->numbertilde_04_setupDone = true;
                            this->numbertilde_04_smooth_d_dspsetup();
                        }
                        
                        number tri_tilde_02_dcblocker_next(number x, number gain) {
                            number y = x - this->tri_tilde_02_dcblocker_xm1 + this->tri_tilde_02_dcblocker_ym1 * gain;
                            this->tri_tilde_02_dcblocker_xm1 = x;
                            this->tri_tilde_02_dcblocker_ym1 = y;
                            return y;
                        }
                        
                        void tri_tilde_02_dcblocker_reset() {
                            this->tri_tilde_02_dcblocker_xm1 = 0;
                            this->tri_tilde_02_dcblocker_ym1 = 0;
                        }
                        
                        void tri_tilde_02_dcblocker_dspsetup() {
                            this->tri_tilde_02_dcblocker_reset();
                        }
                        
                        void tri_tilde_02_dspsetup(bool force) {
                            if ((bool)(this->tri_tilde_02_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->tri_tilde_02_setupDone = true;
                            this->tri_tilde_02_dcblocker_dspsetup();
                        }
                        
                        void ip_04_init() {
                            this->ip_04_lastValue = this->ip_04_value;
                        }
                        
                        void ip_04_dspsetup(bool force) {
                            if ((bool)(this->ip_04_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->ip_04_lastIndex = 0;
                            this->ip_04_setupDone = true;
                        }
                        
                        number rect_tilde_03_rectangle(number phase, number pulsewidth) {
                            if (phase < pulsewidth) {
                                return 1;
                            } else {
                                return -1;
                            }
                        }
                        
                        number rect_tilde_04_rectangle(number phase, number pulsewidth) {
                            if (phase < pulsewidth) {
                                return 1;
                            } else {
                                return -1;
                            }
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            numberobj_02_value = 0;
                            numberobj_02_value_setter(numberobj_02_value);
                            expr_03_in1 = 0;
                            expr_03_in2 = 1;
                            expr_03_out1 = 0;
                            selector_04_onoff = 1;
                            param_09_value = 2;
                            cycle_tilde_02_frequency = 0;
                            cycle_tilde_02_phase_offset = 0;
                            numbertilde_03_input_number = 0;
                            numbertilde_03_ramp = 0;
                            saw_tilde_02_frequency = 0;
                            saw_tilde_02_syncPhase = 0;
                            numbertilde_04_input_number = 0;
                            numbertilde_04_ramp = 0;
                            tri_tilde_02_frequency = 0;
                            tri_tilde_02_pulsewidth = 0.5;
                            tri_tilde_02_syncPhase = 0;
                            selector_05_onoff = 1;
                            ip_04_value = 0;
                            ip_04_impulse = 0;
                            rect_tilde_03_frequency = 440;
                            rect_tilde_03_pulsewidth = 0.5;
                            rect_tilde_03_syncPhase = 0;
                            rect_tilde_04_frequency = 0;
                            rect_tilde_04_pulsewidth = 0.5;
                            rect_tilde_04_syncPhase = 0;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            signals[1] = nullptr;
                            signals[2] = nullptr;
                            signals[3] = nullptr;
                            signals[4] = nullptr;
                            signals[5] = nullptr;
                            signals[6] = nullptr;
                            signals[7] = nullptr;
                            signals[8] = nullptr;
                            signals[9] = nullptr;
                            signals[10] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            numberobj_02_currentFormat = 6;
                            numberobj_02_lastValue = 0;
                            param_09_lastValue = 0;
                            cycle_tilde_02_wrap = 0;
                            cycle_tilde_02_ph_currentPhase = 0;
                            cycle_tilde_02_ph_conv = 0;
                            cycle_tilde_02_setupDone = false;
                            numbertilde_03_currentInterval = 0;
                            numbertilde_03_currentIntervalInSamples = 0;
                            numbertilde_03_lastValue = 0;
                            numbertilde_03_outValue = 0;
                            numbertilde_03_rampInSamples = 0;
                            numbertilde_03_currentMode = 0;
                            numbertilde_03_smooth_d_prev = 0;
                            numbertilde_03_smooth_prev = 0;
                            numbertilde_03_smooth_index = 0;
                            numbertilde_03_smooth_increment = 0;
                            numbertilde_03_setupDone = false;
                            saw_tilde_02_t = 0;
                            saw_tilde_02_lastSyncPhase = 0;
                            saw_tilde_02_lastSyncDiff = 0;
                            saw_tilde_02_didSync = false;
                            saw_tilde_02_dcblocker_xm1 = 0;
                            saw_tilde_02_dcblocker_ym1 = 0;
                            saw_tilde_02_setupDone = false;
                            numbertilde_04_currentInterval = 0;
                            numbertilde_04_currentIntervalInSamples = 0;
                            numbertilde_04_lastValue = 0;
                            numbertilde_04_outValue = 0;
                            numbertilde_04_rampInSamples = 0;
                            numbertilde_04_currentMode = 0;
                            numbertilde_04_smooth_d_prev = 0;
                            numbertilde_04_smooth_prev = 0;
                            numbertilde_04_smooth_index = 0;
                            numbertilde_04_smooth_increment = 0;
                            numbertilde_04_setupDone = false;
                            tri_tilde_02_t = 0;
                            tri_tilde_02_lastSyncPhase = 0;
                            tri_tilde_02_lastSyncDiff = 0;
                            tri_tilde_02_didSync = false;
                            tri_tilde_02_yn = 0;
                            tri_tilde_02_yn1 = 0;
                            tri_tilde_02_yn2 = 0;
                            tri_tilde_02_yn3 = 0;
                            tri_tilde_02_flg = 0;
                            tri_tilde_02_app_correction = 0;
                            tri_tilde_02_dcblocker_xm1 = 0;
                            tri_tilde_02_dcblocker_ym1 = 0;
                            tri_tilde_02_setupDone = false;
                            ip_04_lastIndex = 0;
                            ip_04_lastValue = 0;
                            ip_04_resetCount = 0;
                            ip_04_sigbuf = nullptr;
                            ip_04_setupDone = false;
                            rect_tilde_03_xHistory = 0;
                            rect_tilde_03_yHistory = 0;
                            rect_tilde_03_t = 0;
                            rect_tilde_03_lastSyncPhase = 0;
                            rect_tilde_03_lastSyncDiff = 0;
                            rect_tilde_03_didSync = false;
                            rect_tilde_04_xHistory = 0;
                            rect_tilde_04_yHistory = 0;
                            rect_tilde_04_t = 0;
                            rect_tilde_04_lastSyncPhase = 0;
                            rect_tilde_04_lastSyncDiff = 0;
                            rect_tilde_04_didSync = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number numberobj_02_value;
                            number expr_03_in1;
                            number expr_03_in2;
                            number expr_03_out1;
                            number selector_04_onoff;
                            number param_09_value;
                            number cycle_tilde_02_frequency;
                            number cycle_tilde_02_phase_offset;
                            number numbertilde_03_input_number;
                            number numbertilde_03_ramp;
                            number saw_tilde_02_frequency;
                            number saw_tilde_02_syncPhase;
                            number numbertilde_04_input_number;
                            number numbertilde_04_ramp;
                            number tri_tilde_02_frequency;
                            number tri_tilde_02_pulsewidth;
                            number tri_tilde_02_syncPhase;
                            number selector_05_onoff;
                            number ip_04_value;
                            number ip_04_impulse;
                            number rect_tilde_03_frequency;
                            number rect_tilde_03_pulsewidth;
                            number rect_tilde_03_syncPhase;
                            number rect_tilde_04_frequency;
                            number rect_tilde_04_pulsewidth;
                            number rect_tilde_04_syncPhase;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[11];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            Int numberobj_02_currentFormat;
                            number numberobj_02_lastValue;
                            number param_09_lastValue;
                            UInt noise_tilde_02_state[4] = { };
                            Float64BufferRef cycle_tilde_02_buffer;
                            long cycle_tilde_02_wrap;
                            uint32_t cycle_tilde_02_phasei;
                            SampleValue cycle_tilde_02_f2i;
                            number cycle_tilde_02_ph_currentPhase;
                            number cycle_tilde_02_ph_conv;
                            bool cycle_tilde_02_setupDone;
                            SampleIndex numbertilde_03_currentInterval;
                            SampleIndex numbertilde_03_currentIntervalInSamples;
                            number numbertilde_03_lastValue;
                            number numbertilde_03_outValue;
                            number numbertilde_03_rampInSamples;
                            Int numbertilde_03_currentMode;
                            number numbertilde_03_smooth_d_prev;
                            number numbertilde_03_smooth_prev;
                            number numbertilde_03_smooth_index;
                            number numbertilde_03_smooth_increment;
                            bool numbertilde_03_setupDone;
                            number saw_tilde_02_t;
                            number saw_tilde_02_lastSyncPhase;
                            number saw_tilde_02_lastSyncDiff;
                            bool saw_tilde_02_didSync;
                            number saw_tilde_02_dcblocker_xm1;
                            number saw_tilde_02_dcblocker_ym1;
                            bool saw_tilde_02_setupDone;
                            SampleIndex numbertilde_04_currentInterval;
                            SampleIndex numbertilde_04_currentIntervalInSamples;
                            number numbertilde_04_lastValue;
                            number numbertilde_04_outValue;
                            number numbertilde_04_rampInSamples;
                            Int numbertilde_04_currentMode;
                            number numbertilde_04_smooth_d_prev;
                            number numbertilde_04_smooth_prev;
                            number numbertilde_04_smooth_index;
                            number numbertilde_04_smooth_increment;
                            bool numbertilde_04_setupDone;
                            number tri_tilde_02_t;
                            number tri_tilde_02_lastSyncPhase;
                            number tri_tilde_02_lastSyncDiff;
                            bool tri_tilde_02_didSync;
                            number tri_tilde_02_yn;
                            number tri_tilde_02_yn1;
                            number tri_tilde_02_yn2;
                            number tri_tilde_02_yn3;
                            number tri_tilde_02_flg;
                            number tri_tilde_02_app_correction;
                            number tri_tilde_02_dcblocker_xm1;
                            number tri_tilde_02_dcblocker_ym1;
                            bool tri_tilde_02_setupDone;
                            SampleIndex ip_04_lastIndex;
                            number ip_04_lastValue;
                            SampleIndex ip_04_resetCount;
                            signal ip_04_sigbuf;
                            bool ip_04_setupDone;
                            number rect_tilde_03_xHistory;
                            number rect_tilde_03_yHistory;
                            number rect_tilde_03_t;
                            number rect_tilde_03_lastSyncPhase;
                            number rect_tilde_03_lastSyncDiff;
                            bool rect_tilde_03_didSync;
                            number rect_tilde_04_xHistory;
                            number rect_tilde_04_yHistory;
                            number rect_tilde_04_t;
                            number rect_tilde_04_lastSyncPhase;
                            number rect_tilde_04_lastSyncDiff;
                            bool rect_tilde_04_didSync;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            class RNBOSubpatcher_63 : public PatcherInterfaceImpl {
                        
                        friend class RNBOSubpatcher_66;
                        friend class rnbomatic;
                        
                        public:
                        
                        RNBOSubpatcher_63()
                        {
                        }
                        
                        ~RNBOSubpatcher_63()
                        {
                        }
                        
                        virtual RNBOSubpatcher_66* getPatcher() const {
                            return static_cast<RNBOSubpatcher_66 *>(_parentPatcher);
                        }
                        
                        rnbomatic* getTopLevelPatcher() {
                            return this->getPatcher()->getTopLevelPatcher();
                        }
                        
                        void cancelClockEvents()
                        {
                            getEngine()->flushClockEvents(this, 2098551528, false);
                            getEngine()->flushClockEvents(this, -1494586265, false);
                        }
                        
                        Index voice() {
                            return this->_voiceIndex;
                        }
                        
                        number random(number low, number high) {
                            number range = high - low;
                            return globalrandom() * range + low;
                        }
                        
                        number samplerate() const {
                            return this->sr;
                        }
                        
                        number mstosamps(MillisecondTime ms) {
                            return ms * this->sr * 0.001;
                        }
                        
                        Index getNumMidiInputPorts() const {
                            return 0;
                        }
                        
                        void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
                        
                        Index getNumMidiOutputPorts() const {
                            return 0;
                        }
                        
                        void process(
                            const SampleValue * const* inputs,
                            Index numInputs,
                            SampleValue * const* outputs,
                            Index numOutputs,
                            Index n
                        ) {
                            this->vs = n;
                            this->updateTime(this->getEngine()->getCurrentTime());
                            SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                            SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
                            const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                            const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
                            this->noise_tilde_03_perform(this->signals[0], n);
                        
                            this->cycle_tilde_03_perform(
                                in1,
                                this->cycle_tilde_03_phase_offset,
                                this->signals[1],
                                this->signals[2],
                                n
                            );
                        
                            this->numbertilde_05_perform(in1, this->dummyBuffer, n);
                            this->saw_tilde_03_perform(in1, this->saw_tilde_03_syncPhase, this->signals[3], this->signals[4], n);
                        
                            this->rect_tilde_05_perform(
                                in1,
                                in2,
                                this->rect_tilde_05_syncPhase,
                                this->signals[5],
                                this->signals[6],
                                n
                            );
                        
                            this->tri_tilde_03_perform(
                                in1,
                                in2,
                                this->tri_tilde_03_syncPhase,
                                this->signals[7],
                                this->signals[8],
                                n
                            );
                        
                            this->numbertilde_06_perform(in2, this->dummyBuffer, n);
                        
                            this->rect_tilde_06_perform(
                                in1,
                                in2,
                                this->rect_tilde_06_syncPhase,
                                this->signals[9],
                                this->signals[10],
                                n
                            );
                        
                            this->selector_06_perform(
                                this->selector_06_onoff,
                                this->signals[0],
                                this->signals[1],
                                this->signals[3],
                                this->signals[7],
                                this->signals[5],
                                this->signals[9],
                                out1,
                                n
                            );
                        
                            this->ip_05_perform(this->signals[9], n);
                        
                            this->selector_07_perform(
                                this->selector_07_onoff,
                                this->signals[9],
                                this->signals[2],
                                this->signals[4],
                                this->signals[8],
                                this->signals[6],
                                this->signals[10],
                                out2,
                                n
                            );
                        
                            this->stackprotect_perform(n);
                            this->audioProcessSampleCount += this->vs;
                        }
                        
                        void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                            if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                                Index i;
                        
                                for (i = 0; i < 11; i++) {
                                    this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                                }
                        
                                this->ip_05_sigbuf = resizeSignal(this->ip_05_sigbuf, this->maxvs, maxBlockSize);
                                this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                                this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                                this->didAllocateSignals = true;
                            }
                        
                            const bool sampleRateChanged = sampleRate != this->sr;
                            const bool maxvsChanged = maxBlockSize != this->maxvs;
                            const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
                        
                            if (sampleRateChanged || maxvsChanged) {
                                this->vs = maxBlockSize;
                                this->maxvs = maxBlockSize;
                                this->sr = sampleRate;
                                this->invsr = 1 / sampleRate;
                            }
                        
                            this->cycle_tilde_03_dspsetup(forceDSPSetup);
                            this->numbertilde_05_dspsetup(forceDSPSetup);
                            this->saw_tilde_03_dspsetup(forceDSPSetup);
                            this->tri_tilde_03_dspsetup(forceDSPSetup);
                            this->numbertilde_06_dspsetup(forceDSPSetup);
                            this->ip_05_dspsetup(forceDSPSetup);
                        
                            if (sampleRateChanged)
                                this->onSampleRateChanged(sampleRate);
                        }
                        
                        void setProbingTarget(MessageTag id) {
                            switch (id) {
                            default:
                                {
                                this->setProbingIndex(-1);
                                break;
                                }
                            }
                        }
                        
                        void setProbingIndex(ProbingIndex ) {}
                        
                        Index getProbingChannels(MessageTag outletId) const {
                            RNBO_UNUSED(outletId);
                            return 0;
                        }
                        
                        void setVoiceIndex(Index index)  {
                            this->_voiceIndex = index;
                        }
                        
                        void setNoteNumber(Int noteNumber)  {
                            this->_noteNumber = noteNumber;
                        }
                        
                        Index getIsMuted()  {
                            return this->isMuted;
                        }
                        
                        void setIsMuted(Index v)  {
                            this->isMuted = v;
                        }
                        
                        void onSampleRateChanged(double ) {}
                        
                        Index getPatcherSerial() const {
                            return 0;
                        }
                        
                        void getState(PatcherStateInterface& ) {}
                        
                        void setState() {}
                        
                        void getPreset(PatcherStateInterface& preset) {
                            this->param_10_getPresetValue(getSubState(preset, "mode"));
                        }
                        
                        void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                            this->updateTime(time);
                        
                            switch (index) {
                            case 0:
                                {
                                this->param_10_value_set(v);
                                break;
                                }
                            }
                        }
                        
                        void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValue(index, value, time);
                        }
                        
                        void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                            this->setParameterValue(index, this->getParameterValue(index), time);
                        }
                        
                        void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                            this->setParameterValueNormalized(index, value, time);
                        }
                        
                        ParameterValue getParameterValue(ParameterIndex index)  {
                            switch (index) {
                            case 0:
                                {
                                return this->param_10_value;
                                }
                            default:
                                {
                                return 0;
                                }
                            }
                        }
                        
                        ParameterIndex getNumSignalInParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumSignalOutParameters() const {
                            return 0;
                        }
                        
                        ParameterIndex getNumParameters() const {
                            return 1;
                        }
                        
                        ConstCharPointer getParameterName(ParameterIndex index) const {
                            switch (index) {
                            case 0:
                                {
                                return "mode";
                                }
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        ConstCharPointer getParameterId(ParameterIndex index) const {
                            switch (index) {
                            case 0:
                                {
                                return "poly/oscillators/oscC/mode";
                                }
                            default:
                                {
                                return "bogus";
                                }
                            }
                        }
                        
                        void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                            {
                                switch (index) {
                                case 0:
                                    {
                                    info->type = ParameterTypeNumber;
                                    info->initialValue = 2;
                                    info->min = 0;
                                    info->max = 5;
                                    info->exponent = 1;
                                    info->steps = 6;
                                    static const char * eVal0[] = {"noise", "sine", "saw", "triangle", "square", "pulse"};
                                    info->enumValues = eVal0;
                                    info->debug = false;
                                    info->saveable = true;
                                    info->transmittable = true;
                                    info->initialized = true;
                                    info->visible = true;
                                    info->displayName = "";
                                    info->unit = "";
                                    info->ioType = IOTypeUndefined;
                                    info->signalIndex = INVALID_INDEX;
                                    break;
                                    }
                                }
                            }
                        }
                        
                        void sendParameter(ParameterIndex index, bool ignoreValue) {
                            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
                        }
                        
                        void setParameterOffset(ParameterIndex offset) {
                            this->parameterOffset = offset;
                        }
                        
                        ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                            if (steps == 1) {
                                if (normalizedValue > 0) {
                                    normalizedValue = 1.;
                                }
                            } else {
                                ParameterValue oneStep = (number)1. / (steps - 1);
                                ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                                normalizedValue = numberOfSteps * oneStep;
                            }
                        
                            return normalizedValue;
                        }
                        
                        ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            case 0:
                                {
                                {
                                    value = (value < 0 ? 0 : (value > 5 ? 5 : value));
                                    ParameterValue normalizedValue = (value - 0) / (5 - 0);
                        
                                    {
                                        normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 6);
                                    }
                        
                                    return normalizedValue;
                                }
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        
                            switch (index) {
                            case 0:
                                {
                                {
                                    {
                                        value = this->applyStepsToNormalizedParameterValue(value, 6);
                                    }
                        
                                    {
                                        return 0 + value * (5 - 0);
                                    }
                                }
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                            switch (index) {
                            case 0:
                                {
                                return this->param_10_value_constrain(value);
                                }
                            default:
                                {
                                return value;
                                }
                            }
                        }
                        
                        void scheduleParamInit(ParameterIndex index, Index order) {
                            this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
                        }
                        
                        void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                            RNBO_UNUSED(hasValue);
                            this->updateTime(time);
                        
                            switch (index) {
                            case 2098551528:
                                {
                                this->numbertilde_05_value_set(value);
                                break;
                                }
                            case -1494586265:
                                {
                                this->numbertilde_06_value_set(value);
                                break;
                                }
                            }
                        }
                        
                        void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
                        
                        void processOutletEvent(
                            EngineLink* sender,
                            OutletIndex index,
                            ParameterValue value,
                            MillisecondTime time
                        ) {
                            this->updateTime(time);
                            this->processOutletAtCurrentTime(sender, index, value);
                        }
                        
                        void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("valin"):
                                {
                                if (TAG("poly/oscillators/oscC/number_obj-39") == objectId)
                                    this->numberobj_03_valin_set(payload);
                        
                                break;
                                }
                            case TAG("format"):
                                {
                                if (TAG("poly/oscillators/oscC/number_obj-39") == objectId)
                                    this->numberobj_03_format_set(payload);
                        
                                break;
                                }
                            case TAG("sig"):
                                {
                                if (TAG("poly/oscillators/oscC/number~_obj-18") == objectId)
                                    this->numbertilde_05_sig_number_set(payload);
                        
                                if (TAG("poly/oscillators/oscC/number~_obj-25") == objectId)
                                    this->numbertilde_06_sig_number_set(payload);
                        
                                break;
                                }
                            case TAG("mode"):
                                {
                                if (TAG("poly/oscillators/oscC/number~_obj-18") == objectId)
                                    this->numbertilde_05_mode_set(payload);
                        
                                if (TAG("poly/oscillators/oscC/number~_obj-25") == objectId)
                                    this->numbertilde_06_mode_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processListMessage(
                            MessageTag tag,
                            MessageTag objectId,
                            MillisecondTime time,
                            const list& payload
                        ) {
                            this->updateTime(time);
                        
                            switch (tag) {
                            case TAG("sig"):
                                {
                                if (TAG("poly/oscillators/oscC/number~_obj-18") == objectId)
                                    this->numbertilde_05_sig_list_set(payload);
                        
                                if (TAG("poly/oscillators/oscC/number~_obj-25") == objectId)
                                    this->numbertilde_06_sig_list_set(payload);
                        
                                break;
                                }
                            }
                        }
                        
                        void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
                        
                        MessageTagInfo resolveTag(MessageTag tag) const {
                            switch (tag) {
                            case TAG("valout"):
                                {
                                return "valout";
                                }
                            case TAG("poly/oscillators/oscC/number_obj-39"):
                                {
                                return "poly/oscillators/oscC/number_obj-39";
                                }
                            case TAG("setup"):
                                {
                                return "setup";
                                }
                            case TAG("monitor"):
                                {
                                return "monitor";
                                }
                            case TAG("poly/oscillators/oscC/number~_obj-18"):
                                {
                                return "poly/oscillators/oscC/number~_obj-18";
                                }
                            case TAG("assign"):
                                {
                                return "assign";
                                }
                            case TAG("poly/oscillators/oscC/number~_obj-25"):
                                {
                                return "poly/oscillators/oscC/number~_obj-25";
                                }
                            case TAG("valin"):
                                {
                                return "valin";
                                }
                            case TAG("format"):
                                {
                                return "format";
                                }
                            case TAG("sig"):
                                {
                                return "sig";
                                }
                            case TAG("mode"):
                                {
                                return "mode";
                                }
                            }
                        
                            return nullptr;
                        }
                        
                        DataRef* getDataRef(DataRefIndex index)  {
                            switch (index) {
                            default:
                                {
                                return nullptr;
                                }
                            }
                        }
                        
                        DataRefIndex getNumDataRefs() const {
                            return 0;
                        }
                        
                        void fillDataRef(DataRefIndex , DataRef& ) {}
                        
                        void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                            this->updateTime(time);
                        
                            if (index == 1) {
                                this->cycle_tilde_03_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                                this->cycle_tilde_03_bufferUpdated();
                            }
                        }
                        
                        void initialize() {
                            this->assign_defaults();
                            this->setState();
                            this->cycle_tilde_03_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->getPatcher()->RNBODefaultSinus);
                        }
                        
                        protected:
                        
                        void param_10_value_set(number v) {
                            v = this->param_10_value_constrain(v);
                            this->param_10_value = v;
                            this->sendParameter(0, false);
                        
                            if (this->param_10_value != this->param_10_lastValue) {
                                this->getEngine()->presetTouched();
                                this->param_10_lastValue = this->param_10_value;
                            }
                        
                            this->expr_04_in1_set(v);
                            this->numberobj_03_value_set(v);
                        }
                        
                        void numberobj_03_valin_set(number v) {
                            this->numberobj_03_value_set(v);
                        }
                        
                        void numberobj_03_format_set(number v) {
                            this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
                        }
                        
                        void numbertilde_05_sig_number_set(number v) {
                            this->numbertilde_05_outValue = v;
                        }
                        
                        void numbertilde_05_sig_list_set(const list& v) {
                            this->numbertilde_05_outValue = v[0];
                        }
                        
                        void numbertilde_05_mode_set(number v) {
                            if (v == 1) {
                                this->numbertilde_05_currentMode = 0;
                            } else if (v == 2) {
                                this->numbertilde_05_currentMode = 1;
                            }
                        }
                        
                        void numbertilde_06_sig_number_set(number v) {
                            this->numbertilde_06_outValue = v;
                        }
                        
                        void numbertilde_06_sig_list_set(const list& v) {
                            this->numbertilde_06_outValue = v[0];
                        }
                        
                        void numbertilde_06_mode_set(number v) {
                            if (v == 1) {
                                this->numbertilde_06_currentMode = 0;
                            } else if (v == 2) {
                                this->numbertilde_06_currentMode = 1;
                            }
                        }
                        
                        void numbertilde_05_value_set(number ) {}
                        
                        void numbertilde_06_value_set(number ) {}
                        
                        number msToSamps(MillisecondTime ms, number sampleRate) {
                            return ms * sampleRate * 0.001;
                        }
                        
                        MillisecondTime sampsToMs(SampleIndex samps) {
                            return samps * (this->invsr * 1000);
                        }
                        
                        Index getMaxBlockSize() const {
                            return this->maxvs;
                        }
                        
                        number getSampleRate() const {
                            return this->sr;
                        }
                        
                        bool hasFixedVectorSize() const {
                            return false;
                        }
                        
                        Index getNumInputChannels() const {
                            return 2;
                        }
                        
                        Index getNumOutputChannels() const {
                            return 2;
                        }
                        
                        void initializeObjects() {
                            this->numberobj_03_init();
                            this->noise_tilde_03_init();
                            this->numbertilde_05_init();
                            this->numbertilde_06_init();
                            this->ip_05_init();
                        }
                        
                        void sendOutlet(OutletIndex index, ParameterValue value) {
                            this->getEngine()->sendOutlet(this, index, value);
                        }
                        
                        void startup() {
                            this->updateTime(this->getEngine()->getCurrentTime());
                        
                            {
                                this->scheduleParamInit(0, 0);
                            }
                        }
                        
                        void allocateDataRefs() {
                            this->cycle_tilde_03_buffer->requestSize(16384, 1);
                            this->cycle_tilde_03_buffer->setSampleRate(this->sr);
                            this->cycle_tilde_03_buffer = this->cycle_tilde_03_buffer->allocateIfNeeded();
                        }
                        
                        number param_10_value_constrain(number v) const {
                            v = (v > 5 ? 5 : (v < 0 ? 0 : v));
                        
                            {
                                number oneStep = (number)5 / (number)5;
                                number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
                                number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
                                v = numberOfSteps * oneStep;
                            }
                        
                            return v;
                        }
                        
                        void selector_07_onoff_set(number v) {
                            this->selector_07_onoff = v;
                        }
                        
                        void selector_06_onoff_set(number v) {
                            this->selector_06_onoff = v;
                        }
                        
                        void expr_04_out1_set(number v) {
                            this->expr_04_out1 = v;
                            this->selector_07_onoff_set(this->expr_04_out1);
                            this->selector_06_onoff_set(this->expr_04_out1);
                        }
                        
                        void expr_04_in1_set(number in1) {
                            this->expr_04_in1 = in1;
                            this->expr_04_out1_set(this->expr_04_in1 + this->expr_04_in2);//#map:oscillators/oscC/+_obj-7:1
                        }
                        
                        void numberobj_03_output_set(number ) {}
                        
                        void numberobj_03_value_set(number v) {
                            this->numberobj_03_value_setter(v);
                            v = this->numberobj_03_value;
                            number localvalue = v;
                        
                            if (this->numberobj_03_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->getEngine()->sendNumMessage(
                                TAG("valout"),
                                TAG("poly/oscillators/oscC/number_obj-39"),
                                localvalue,
                                this->_currentTime
                            );
                        
                            this->numberobj_03_output_set(localvalue);
                        }
                        
                        void noise_tilde_03_perform(SampleValue * out1, Index n) {
                            auto __noise_tilde_03_state = this->noise_tilde_03_state;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                out1[(Index)i] = xoshiro_next(__noise_tilde_03_state);
                            }
                        }
                        
                        void cycle_tilde_03_perform(
                            const Sample * frequency,
                            number phase_offset,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(phase_offset);
                            auto __cycle_tilde_03_f2i = this->cycle_tilde_03_f2i;
                            auto __cycle_tilde_03_buffer = this->cycle_tilde_03_buffer;
                            auto __cycle_tilde_03_phasei = this->cycle_tilde_03_phasei;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                {
                                    uint32_t uint_phase;
                        
                                    {
                                        {
                                            uint_phase = __cycle_tilde_03_phasei;
                                        }
                                    }
                        
                                    uint32_t idx = (uint32_t)(uint32_rshift(uint_phase, 18));
                                    number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
                                    number y0 = __cycle_tilde_03_buffer[(Index)idx];
                                    number y1 = __cycle_tilde_03_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
                                    number y = y0 + frac * (y1 - y0);
                        
                                    {
                                        uint32_t pincr = (uint32_t)(uint32_trunc(frequency[(Index)i] * __cycle_tilde_03_f2i));
                                        __cycle_tilde_03_phasei = uint32_add(__cycle_tilde_03_phasei, pincr);
                                    }
                        
                                    out1[(Index)i] = y;
                                    out2[(Index)i] = uint_phase * 0.232830643653869629e-9;
                                    continue;
                                }
                            }
                        
                            this->cycle_tilde_03_phasei = __cycle_tilde_03_phasei;
                        }
                        
                        void numbertilde_05_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
                            auto __numbertilde_05_currentIntervalInSamples = this->numbertilde_05_currentIntervalInSamples;
                            auto __numbertilde_05_lastValue = this->numbertilde_05_lastValue;
                            auto __numbertilde_05_currentInterval = this->numbertilde_05_currentInterval;
                            auto __numbertilde_05_rampInSamples = this->numbertilde_05_rampInSamples;
                            auto __numbertilde_05_outValue = this->numbertilde_05_outValue;
                            auto __numbertilde_05_currentMode = this->numbertilde_05_currentMode;
                            number monitorvalue = input_signal[0];
                        
                            for (Index i = 0; i < n; i++) {
                                if (__numbertilde_05_currentMode == 0) {
                                    output[(Index)i] = this->numbertilde_05_smooth_next(
                                        __numbertilde_05_outValue,
                                        __numbertilde_05_rampInSamples,
                                        __numbertilde_05_rampInSamples
                                    );
                                } else {
                                    output[(Index)i] = input_signal[(Index)i];
                                }
                            }
                        
                            __numbertilde_05_currentInterval -= n;
                        
                            if (monitorvalue != __numbertilde_05_lastValue && __numbertilde_05_currentInterval <= 0) {
                                __numbertilde_05_currentInterval = __numbertilde_05_currentIntervalInSamples;
                        
                                this->getEngine()->scheduleClockEventWithValue(
                                    this,
                                    2098551528,
                                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                                    monitorvalue
                                );;
                        
                                __numbertilde_05_lastValue = monitorvalue;
                        
                                this->getEngine()->sendListMessage(
                                    TAG("monitor"),
                                    TAG("poly/oscillators/oscC/number~_obj-18"),
                                    {monitorvalue},
                                    this->_currentTime
                                );;
                            }
                        
                            this->numbertilde_05_currentInterval = __numbertilde_05_currentInterval;
                            this->numbertilde_05_lastValue = __numbertilde_05_lastValue;
                        }
                        
                        void saw_tilde_03_perform(
                            const Sample * frequency,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __saw_tilde_03_didSync = this->saw_tilde_03_didSync;
                            auto __saw_tilde_03_lastSyncDiff = this->saw_tilde_03_lastSyncDiff;
                            auto __saw_tilde_03_lastSyncPhase = this->saw_tilde_03_lastSyncPhase;
                            auto __saw_tilde_03_t = this->saw_tilde_03_t;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number dt = frequency[(Index)i] / this->samplerate();
                                number t1 = __saw_tilde_03_t + 0.5;
                                t1 -= trunc(t1);
                                number y = 2 * t1 - 1;
                        
                                if (dt != 0.0) {
                                    number syncDiff = 0 - __saw_tilde_03_lastSyncPhase;
                                    __saw_tilde_03_lastSyncPhase = 0;
                                    __saw_tilde_03_lastSyncDiff = syncDiff;
                                    number lookahead = 0 + syncDiff;
                        
                                    if (t1 < dt) {
                                        number d = t1 / dt;
                                        y -= d + d - d * d - 1;
                                    } else if (t1 + dt > 1) {
                                        number d = (t1 - 1) / dt;
                                        y -= d + d + d * d + 1;
                                    } else if ((bool)(__saw_tilde_03_didSync)) {
                                        y = 0;
                                        __saw_tilde_03_didSync = false;
                                    } else if (lookahead > 1) {
                                        y *= 0.5;
                                        __saw_tilde_03_t = 0;
                                        __saw_tilde_03_didSync = true;
                                    }
                        
                                    __saw_tilde_03_t += dt;
                        
                                    if (dt > 0) {
                                        while (__saw_tilde_03_t >= 1) {
                                            __saw_tilde_03_t -= 1;
                                        }
                                    } else {
                                        while (__saw_tilde_03_t <= 0) {
                                            __saw_tilde_03_t += 1;
                                        }
                                    }
                                }
                        
                                y = this->saw_tilde_03_dcblocker_next(y, 0.9997);
                                out1[(Index)i] = 0.5 * y;
                                out2[(Index)i] = __saw_tilde_03_t;
                            }
                        
                            this->saw_tilde_03_t = __saw_tilde_03_t;
                            this->saw_tilde_03_lastSyncPhase = __saw_tilde_03_lastSyncPhase;
                            this->saw_tilde_03_lastSyncDiff = __saw_tilde_03_lastSyncDiff;
                            this->saw_tilde_03_didSync = __saw_tilde_03_didSync;
                        }
                        
                        void rect_tilde_05_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __rect_tilde_05_xHistory = this->rect_tilde_05_xHistory;
                            auto __rect_tilde_05_yHistory = this->rect_tilde_05_yHistory;
                            auto __rect_tilde_05_didSync = this->rect_tilde_05_didSync;
                            auto __rect_tilde_05_t = this->rect_tilde_05_t;
                            auto __rect_tilde_05_lastSyncDiff = this->rect_tilde_05_lastSyncDiff;
                            auto __rect_tilde_05_lastSyncPhase = this->rect_tilde_05_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                                number pw = pulsewidth[(Index)i];
                        
                                if (pulsewidth[(Index)i] > 0.99) {
                                    pw = 0.99;
                                } else if (pulsewidth[(Index)i] < 0.01) {
                                    pw = 0.01;
                                }
                        
                                number syncDiff = 0 - __rect_tilde_05_lastSyncPhase;
                                __rect_tilde_05_lastSyncPhase = 0;
                                __rect_tilde_05_lastSyncDiff = syncDiff;
                                number syncLookahead = 0 + syncDiff;
                                number tCurr = __rect_tilde_05_t;
                                number tPrev = tCurr - dt;
                                number tNext = tCurr + dt;
                        
                                if (tPrev < 0) {
                                    while (tPrev < 0) {
                                        tPrev += 1;
                                    }
                                }
                        
                                if (tNext > 1) {
                                    while (tNext >= 1) {
                                        tNext -= 1;
                                    }
                                }
                        
                                number yNext = this->rect_tilde_05_rectangle(tNext, pw);
                                number yCurr = this->rect_tilde_05_rectangle(tCurr, pw);
                                number yPrev = this->rect_tilde_05_rectangle(tPrev, pw);
                        
                                if (dt != 0.0) {
                                    if (yPrev < yCurr) {
                                        number d = tCurr / dt;
                                        yCurr += d - 0.5 * d * d - 0.5;
                                    } else if (yCurr < yNext) {
                                        number d = (1 - tCurr) / dt;
                                        yCurr += 0.5 * d * d + d + 0.5;
                                    } else if (yPrev > yCurr) {
                                        number d = (tCurr - pw) / dt;
                                        yCurr -= d - 0.5 * d * d - 0.5;
                                    } else if (yCurr > yNext) {
                                        number d = (pw - tCurr) / dt;
                                        yCurr -= 0.5 * d * d + d + 0.5;
                                    } else if ((bool)(__rect_tilde_05_didSync)) {
                                        yCurr = 0.25;
                                        __rect_tilde_05_didSync = false;
                                    } else if (syncLookahead > 1) {
                                        if (yCurr < 0) {
                                            yCurr = -0.125;
                                        }
                        
                                        __rect_tilde_05_t = 0;
                                        __rect_tilde_05_didSync = true;
                                    }
                        
                                    __rect_tilde_05_t += dt;
                        
                                    if (dt > 0) {
                                        while (__rect_tilde_05_t >= 1) {
                                            __rect_tilde_05_t -= 1;
                                        }
                                    } else {
                                        while (__rect_tilde_05_t <= 0) {
                                            __rect_tilde_05_t += 1;
                                        }
                                    }
                                }
                        
                                number output = yCurr - __rect_tilde_05_yHistory + __rect_tilde_05_xHistory * 0.9997;
                                __rect_tilde_05_xHistory = output;
                                __rect_tilde_05_yHistory = yCurr;
                                out1[(Index)i] = 0.5 * output;
                                out2[(Index)i] = __rect_tilde_05_t;
                            }
                        
                            this->rect_tilde_05_lastSyncPhase = __rect_tilde_05_lastSyncPhase;
                            this->rect_tilde_05_lastSyncDiff = __rect_tilde_05_lastSyncDiff;
                            this->rect_tilde_05_t = __rect_tilde_05_t;
                            this->rect_tilde_05_didSync = __rect_tilde_05_didSync;
                            this->rect_tilde_05_yHistory = __rect_tilde_05_yHistory;
                            this->rect_tilde_05_xHistory = __rect_tilde_05_xHistory;
                        }
                        
                        void tri_tilde_03_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __tri_tilde_03_yn3 = this->tri_tilde_03_yn3;
                            auto __tri_tilde_03_yn2 = this->tri_tilde_03_yn2;
                            auto __tri_tilde_03_yn1 = this->tri_tilde_03_yn1;
                            auto __tri_tilde_03_app_correction = this->tri_tilde_03_app_correction;
                            auto __tri_tilde_03_flg = this->tri_tilde_03_flg;
                            auto __tri_tilde_03_yn = this->tri_tilde_03_yn;
                            auto __tri_tilde_03_t = this->tri_tilde_03_t;
                            auto __tri_tilde_03_lastSyncDiff = this->tri_tilde_03_lastSyncDiff;
                            auto __tri_tilde_03_lastSyncPhase = this->tri_tilde_03_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                        
                                if (dt != 0.0) {
                                    number pw = pulsewidth[(Index)i];
                        
                                    if (pulsewidth[(Index)i] > 0.99) {
                                        pw = 0.99;
                                    } else if (pulsewidth[(Index)i] < 0.01) {
                                        pw = 0.01;
                                    }
                        
                                    number syncDiff = 0 - __tri_tilde_03_lastSyncPhase;
                                    __tri_tilde_03_lastSyncPhase = 0;
                                    __tri_tilde_03_lastSyncDiff = syncDiff;
                                    number syncLookahead = 0 + syncDiff;
                        
                                    if (syncLookahead > 1) {
                                        __tri_tilde_03_t = 0;
                                    }
                        
                                    number tCurr = __tri_tilde_03_t;
                                    number upSlope = __frequency / (pw * this->samplerate());
                                    number downSlope = __frequency / ((1 - pw) * this->samplerate());
                        
                                    if (tCurr <= pw) {
                                        __tri_tilde_03_yn = (number)2 / pw * tCurr - 1;
                        
                                        if (__tri_tilde_03_flg == -1) {
                                            __tri_tilde_03_app_correction = 1;
                                            __tri_tilde_03_flg = 1;
                                        } else if (__tri_tilde_03_app_correction == 1) {
                                            __tri_tilde_03_app_correction = 0;
                                            number d = (tCurr - dt) / dt;
                                            number d2 = d * d;
                                            number d3 = d2 * d;
                                            number d4 = d2 * d2;
                                            number d5 = d * d4;
                                            number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                            number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                            number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                            number h3 = d5 / (number)120;
                                            __tri_tilde_03_yn += upSlope * h0;
                                            __tri_tilde_03_yn1 += upSlope * h1;
                                            __tri_tilde_03_yn2 += upSlope * h2;
                                            __tri_tilde_03_yn3 += upSlope * h3;
                                        }
                        
                                        __tri_tilde_03_flg = 1;
                                    } else {
                                        __tri_tilde_03_yn = 1 - 2 * (tCurr - pw) / (1 - pw);
                        
                                        if (__tri_tilde_03_flg == 1) {
                                            __tri_tilde_03_app_correction = 1;
                                        } else if (__tri_tilde_03_app_correction == 1) {
                                            __tri_tilde_03_app_correction = 0;
                                            number d = (tCurr - pw - dt) / dt;
                                            number d2 = d * d;
                                            number d3 = d2 * d;
                                            number d4 = d2 * d2;
                                            number d5 = d4 * d;
                                            number h0 = -d5 / (number)120 + d4 / (number)24 - d3 / (number)12 + d2 / (number)12 - d / (number)24 + (number)1 / (number)120;
                                            number h1 = d5 / (number)40 - d4 / (number)12 + d2 / (number)3 - d / (number)2 + (number)7 / (number)30;
                                            number h2 = -d5 / (number)40 + d4 / (number)24 + d3 / (number)12 + d2 / (number)12 + d / (number)24 + (number)1 / (number)120;
                                            number h3 = d5 / (number)120;
                                            __tri_tilde_03_yn -= downSlope * h0;
                                            __tri_tilde_03_yn1 -= downSlope * h1;
                                            __tri_tilde_03_yn2 -= downSlope * h2;
                                            __tri_tilde_03_yn3 -= downSlope * h3;
                                        }
                        
                                        __tri_tilde_03_flg = -1;
                                    }
                                }
                        
                                number y = __tri_tilde_03_yn3;
                                __tri_tilde_03_yn3 = __tri_tilde_03_yn2;
                                __tri_tilde_03_yn2 = __tri_tilde_03_yn1;
                                __tri_tilde_03_yn1 = __tri_tilde_03_yn;
                                __tri_tilde_03_t += dt;
                        
                                if (dt > 0) {
                                    while (__tri_tilde_03_t >= 1) {
                                        __tri_tilde_03_t -= 1;
                                    }
                                } else {
                                    while (__tri_tilde_03_t <= 0) {
                                        __tri_tilde_03_t += 1;
                                    }
                                }
                        
                                y = this->tri_tilde_03_dcblocker_next(y, 0.9997);
                                out1[(Index)i] = y * 0.5;
                                out2[(Index)i] = __tri_tilde_03_t;
                            }
                        
                            this->tri_tilde_03_lastSyncPhase = __tri_tilde_03_lastSyncPhase;
                            this->tri_tilde_03_lastSyncDiff = __tri_tilde_03_lastSyncDiff;
                            this->tri_tilde_03_t = __tri_tilde_03_t;
                            this->tri_tilde_03_yn = __tri_tilde_03_yn;
                            this->tri_tilde_03_flg = __tri_tilde_03_flg;
                            this->tri_tilde_03_app_correction = __tri_tilde_03_app_correction;
                            this->tri_tilde_03_yn1 = __tri_tilde_03_yn1;
                            this->tri_tilde_03_yn2 = __tri_tilde_03_yn2;
                            this->tri_tilde_03_yn3 = __tri_tilde_03_yn3;
                        }
                        
                        void numbertilde_06_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
                            auto __numbertilde_06_currentIntervalInSamples = this->numbertilde_06_currentIntervalInSamples;
                            auto __numbertilde_06_lastValue = this->numbertilde_06_lastValue;
                            auto __numbertilde_06_currentInterval = this->numbertilde_06_currentInterval;
                            auto __numbertilde_06_rampInSamples = this->numbertilde_06_rampInSamples;
                            auto __numbertilde_06_outValue = this->numbertilde_06_outValue;
                            auto __numbertilde_06_currentMode = this->numbertilde_06_currentMode;
                            number monitorvalue = input_signal[0];
                        
                            for (Index i = 0; i < n; i++) {
                                if (__numbertilde_06_currentMode == 0) {
                                    output[(Index)i] = this->numbertilde_06_smooth_next(
                                        __numbertilde_06_outValue,
                                        __numbertilde_06_rampInSamples,
                                        __numbertilde_06_rampInSamples
                                    );
                                } else {
                                    output[(Index)i] = input_signal[(Index)i];
                                }
                            }
                        
                            __numbertilde_06_currentInterval -= n;
                        
                            if (monitorvalue != __numbertilde_06_lastValue && __numbertilde_06_currentInterval <= 0) {
                                __numbertilde_06_currentInterval = __numbertilde_06_currentIntervalInSamples;
                        
                                this->getEngine()->scheduleClockEventWithValue(
                                    this,
                                    -1494586265,
                                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                                    monitorvalue
                                );;
                        
                                __numbertilde_06_lastValue = monitorvalue;
                        
                                this->getEngine()->sendListMessage(
                                    TAG("monitor"),
                                    TAG("poly/oscillators/oscC/number~_obj-25"),
                                    {monitorvalue},
                                    this->_currentTime
                                );;
                            }
                        
                            this->numbertilde_06_currentInterval = __numbertilde_06_currentInterval;
                            this->numbertilde_06_lastValue = __numbertilde_06_lastValue;
                        }
                        
                        void rect_tilde_06_perform(
                            const Sample * frequency,
                            const Sample * pulsewidth,
                            number syncPhase,
                            SampleValue * out1,
                            SampleValue * out2,
                            Index n
                        ) {
                            RNBO_UNUSED(syncPhase);
                            auto __rect_tilde_06_xHistory = this->rect_tilde_06_xHistory;
                            auto __rect_tilde_06_yHistory = this->rect_tilde_06_yHistory;
                            auto __rect_tilde_06_didSync = this->rect_tilde_06_didSync;
                            auto __rect_tilde_06_t = this->rect_tilde_06_t;
                            auto __rect_tilde_06_lastSyncDiff = this->rect_tilde_06_lastSyncDiff;
                            auto __rect_tilde_06_lastSyncPhase = this->rect_tilde_06_lastSyncPhase;
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                number __frequency = frequency[(Index)i];
                                __frequency = rnbo_abs(__frequency);
                                number dt = __frequency / this->samplerate();
                                number pw = pulsewidth[(Index)i];
                        
                                if (pulsewidth[(Index)i] > 0.99) {
                                    pw = 0.99;
                                } else if (pulsewidth[(Index)i] < 0.01) {
                                    pw = 0.01;
                                }
                        
                                number syncDiff = 0 - __rect_tilde_06_lastSyncPhase;
                                __rect_tilde_06_lastSyncPhase = 0;
                                __rect_tilde_06_lastSyncDiff = syncDiff;
                                number syncLookahead = 0 + syncDiff;
                                number tCurr = __rect_tilde_06_t;
                                number tPrev = tCurr - dt;
                                number tNext = tCurr + dt;
                        
                                if (tPrev < 0) {
                                    while (tPrev < 0) {
                                        tPrev += 1;
                                    }
                                }
                        
                                if (tNext > 1) {
                                    while (tNext >= 1) {
                                        tNext -= 1;
                                    }
                                }
                        
                                number yNext = this->rect_tilde_06_rectangle(tNext, pw);
                                number yCurr = this->rect_tilde_06_rectangle(tCurr, pw);
                                number yPrev = this->rect_tilde_06_rectangle(tPrev, pw);
                        
                                if (dt != 0.0) {
                                    if (yPrev < yCurr) {
                                        number d = tCurr / dt;
                                        yCurr += d - 0.5 * d * d - 0.5;
                                    } else if (yCurr < yNext) {
                                        number d = (1 - tCurr) / dt;
                                        yCurr += 0.5 * d * d + d + 0.5;
                                    } else if (yPrev > yCurr) {
                                        number d = (tCurr - pw) / dt;
                                        yCurr -= d - 0.5 * d * d - 0.5;
                                    } else if (yCurr > yNext) {
                                        number d = (pw - tCurr) / dt;
                                        yCurr -= 0.5 * d * d + d + 0.5;
                                    } else if ((bool)(__rect_tilde_06_didSync)) {
                                        yCurr = 0.25;
                                        __rect_tilde_06_didSync = false;
                                    } else if (syncLookahead > 1) {
                                        if (yCurr < 0) {
                                            yCurr = -0.125;
                                        }
                        
                                        __rect_tilde_06_t = 0;
                                        __rect_tilde_06_didSync = true;
                                    }
                        
                                    __rect_tilde_06_t += dt;
                        
                                    if (dt > 0) {
                                        while (__rect_tilde_06_t >= 1) {
                                            __rect_tilde_06_t -= 1;
                                        }
                                    } else {
                                        while (__rect_tilde_06_t <= 0) {
                                            __rect_tilde_06_t += 1;
                                        }
                                    }
                                }
                        
                                number output = yCurr - __rect_tilde_06_yHistory + __rect_tilde_06_xHistory * 0.9997;
                                __rect_tilde_06_xHistory = output;
                                __rect_tilde_06_yHistory = yCurr;
                                out1[(Index)i] = 0.5 * output;
                                out2[(Index)i] = __rect_tilde_06_t;
                            }
                        
                            this->rect_tilde_06_lastSyncPhase = __rect_tilde_06_lastSyncPhase;
                            this->rect_tilde_06_lastSyncDiff = __rect_tilde_06_lastSyncDiff;
                            this->rect_tilde_06_t = __rect_tilde_06_t;
                            this->rect_tilde_06_didSync = __rect_tilde_06_didSync;
                            this->rect_tilde_06_yHistory = __rect_tilde_06_yHistory;
                            this->rect_tilde_06_xHistory = __rect_tilde_06_xHistory;
                        }
                        
                        void selector_06_perform(
                            number onoff,
                            const SampleValue * in1,
                            const SampleValue * in2,
                            const SampleValue * in3,
                            const SampleValue * in4,
                            const SampleValue * in5,
                            const SampleValue * in6,
                            SampleValue * out,
                            Index n
                        ) {
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                if (onoff >= 1 && onoff < 2)
                                    out[(Index)i] = in1[(Index)i];
                                else if (onoff >= 2 && onoff < 3)
                                    out[(Index)i] = in2[(Index)i];
                                else if (onoff >= 3 && onoff < 4)
                                    out[(Index)i] = in3[(Index)i];
                                else if (onoff >= 4 && onoff < 5)
                                    out[(Index)i] = in4[(Index)i];
                                else if (onoff >= 5 && onoff < 6)
                                    out[(Index)i] = in5[(Index)i];
                                else if (onoff >= 6 && onoff < 7)
                                    out[(Index)i] = in6[(Index)i];
                                else
                                    out[(Index)i] = 0;
                            }
                        }
                        
                        void ip_05_perform(SampleValue * out, Index n) {
                            auto __ip_05_lastValue = this->ip_05_lastValue;
                            auto __ip_05_lastIndex = this->ip_05_lastIndex;
                        
                            for (Index i = 0; i < n; i++) {
                                out[(Index)i] = ((SampleIndex)(i) >= __ip_05_lastIndex ? __ip_05_lastValue : this->ip_05_sigbuf[(Index)i]);
                            }
                        
                            __ip_05_lastIndex = 0;
                            this->ip_05_lastIndex = __ip_05_lastIndex;
                        }
                        
                        void selector_07_perform(
                            number onoff,
                            const SampleValue * in1,
                            const SampleValue * in2,
                            const SampleValue * in3,
                            const SampleValue * in4,
                            const SampleValue * in5,
                            const SampleValue * in6,
                            SampleValue * out,
                            Index n
                        ) {
                            Index i;
                        
                            for (i = 0; i < n; i++) {
                                if (onoff >= 1 && onoff < 2)
                                    out[(Index)i] = in1[(Index)i];
                                else if (onoff >= 2 && onoff < 3)
                                    out[(Index)i] = in2[(Index)i];
                                else if (onoff >= 3 && onoff < 4)
                                    out[(Index)i] = in3[(Index)i];
                                else if (onoff >= 4 && onoff < 5)
                                    out[(Index)i] = in4[(Index)i];
                                else if (onoff >= 5 && onoff < 6)
                                    out[(Index)i] = in5[(Index)i];
                                else if (onoff >= 6 && onoff < 7)
                                    out[(Index)i] = in6[(Index)i];
                                else
                                    out[(Index)i] = 0;
                            }
                        }
                        
                        void stackprotect_perform(Index n) {
                            RNBO_UNUSED(n);
                            auto __stackprotect_count = this->stackprotect_count;
                            __stackprotect_count = 0;
                            this->stackprotect_count = __stackprotect_count;
                        }
                        
                        void numberobj_03_value_setter(number v) {
                            number localvalue = v;
                        
                            if (this->numberobj_03_currentFormat != 6) {
                                localvalue = trunc(localvalue);
                            }
                        
                            this->numberobj_03_value = localvalue;
                        }
                        
                        void numberobj_03_init() {
                            this->numberobj_03_currentFormat = 6;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscC/number_obj-39"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->numberobj_03_value;
                        }
                        
                        void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->numberobj_03_value_set(preset["value"]);
                        }
                        
                        void param_10_getPresetValue(PatcherStateInterface& preset) {
                            preset["value"] = this->param_10_value;
                        }
                        
                        void param_10_setPresetValue(PatcherStateInterface& preset) {
                            if ((bool)(stateIsEmpty(preset)))
                                return;
                        
                            this->param_10_value_set(preset["value"]);
                        }
                        
                        void noise_tilde_03_init() {
                            this->noise_tilde_03_reset();
                        }
                        
                        void noise_tilde_03_reset() {
                            xoshiro_reset(
                                systemticks() + this->voice() + this->random(0, 10000),
                                this->noise_tilde_03_state
                            );
                        }
                        
                        number cycle_tilde_03_ph_next(number freq, number reset) {
                            {
                                {
                                    if (reset >= 0.)
                                        this->cycle_tilde_03_ph_currentPhase = reset;
                                }
                            }
                        
                            number pincr = freq * this->cycle_tilde_03_ph_conv;
                        
                            if (this->cycle_tilde_03_ph_currentPhase < 0.)
                                this->cycle_tilde_03_ph_currentPhase = 1. + this->cycle_tilde_03_ph_currentPhase;
                        
                            if (this->cycle_tilde_03_ph_currentPhase > 1.)
                                this->cycle_tilde_03_ph_currentPhase = this->cycle_tilde_03_ph_currentPhase - 1.;
                        
                            number tmp = this->cycle_tilde_03_ph_currentPhase;
                            this->cycle_tilde_03_ph_currentPhase += pincr;
                            return tmp;
                        }
                        
                        void cycle_tilde_03_ph_reset() {
                            this->cycle_tilde_03_ph_currentPhase = 0;
                        }
                        
                        void cycle_tilde_03_ph_dspsetup() {
                            this->cycle_tilde_03_ph_conv = (number)1 / this->sr;
                        }
                        
                        void cycle_tilde_03_dspsetup(bool force) {
                            if ((bool)(this->cycle_tilde_03_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->cycle_tilde_03_phasei = 0;
                            this->cycle_tilde_03_f2i = (number)4294967296 / this->samplerate();
                            this->cycle_tilde_03_wrap = (long)(this->cycle_tilde_03_buffer->getSize()) - 1;
                            this->cycle_tilde_03_setupDone = true;
                            this->cycle_tilde_03_ph_dspsetup();
                        }
                        
                        void cycle_tilde_03_bufferUpdated() {
                            this->cycle_tilde_03_wrap = (long)(this->cycle_tilde_03_buffer->getSize()) - 1;
                        }
                        
                        number numbertilde_05_smooth_d_next(number x) {
                            number temp = (number)(x - this->numbertilde_05_smooth_d_prev);
                            this->numbertilde_05_smooth_d_prev = x;
                            return temp;
                        }
                        
                        void numbertilde_05_smooth_d_dspsetup() {
                            this->numbertilde_05_smooth_d_reset();
                        }
                        
                        void numbertilde_05_smooth_d_reset() {
                            this->numbertilde_05_smooth_d_prev = 0;
                        }
                        
                        number numbertilde_05_smooth_next(number x, number up, number down) {
                            if (this->numbertilde_05_smooth_d_next(x) != 0.) {
                                if (x > this->numbertilde_05_smooth_prev) {
                                    number _up = up;
                        
                                    if (_up < 1)
                                        _up = 1;
                        
                                    this->numbertilde_05_smooth_index = _up;
                                    this->numbertilde_05_smooth_increment = (x - this->numbertilde_05_smooth_prev) / _up;
                                } else if (x < this->numbertilde_05_smooth_prev) {
                                    number _down = down;
                        
                                    if (_down < 1)
                                        _down = 1;
                        
                                    this->numbertilde_05_smooth_index = _down;
                                    this->numbertilde_05_smooth_increment = (x - this->numbertilde_05_smooth_prev) / _down;
                                }
                            }
                        
                            if (this->numbertilde_05_smooth_index > 0) {
                                this->numbertilde_05_smooth_prev += this->numbertilde_05_smooth_increment;
                                this->numbertilde_05_smooth_index -= 1;
                            } else {
                                this->numbertilde_05_smooth_prev = x;
                            }
                        
                            return this->numbertilde_05_smooth_prev;
                        }
                        
                        void numbertilde_05_smooth_reset() {
                            this->numbertilde_05_smooth_prev = 0;
                            this->numbertilde_05_smooth_index = 0;
                            this->numbertilde_05_smooth_increment = 0;
                            this->numbertilde_05_smooth_d_reset();
                        }
                        
                        void numbertilde_05_init() {
                            this->numbertilde_05_currentMode = 0;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscC/number~_obj-18"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numbertilde_05_dspsetup(bool force) {
                            if ((bool)(this->numbertilde_05_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->numbertilde_05_currentIntervalInSamples = this->mstosamps(100);
                            this->numbertilde_05_currentInterval = this->numbertilde_05_currentIntervalInSamples;
                            this->numbertilde_05_rampInSamples = this->mstosamps(this->numbertilde_05_ramp);
                            this->numbertilde_05_setupDone = true;
                            this->numbertilde_05_smooth_d_dspsetup();
                        }
                        
                        number saw_tilde_03_dcblocker_next(number x, number gain) {
                            number y = x - this->saw_tilde_03_dcblocker_xm1 + this->saw_tilde_03_dcblocker_ym1 * gain;
                            this->saw_tilde_03_dcblocker_xm1 = x;
                            this->saw_tilde_03_dcblocker_ym1 = y;
                            return y;
                        }
                        
                        void saw_tilde_03_dcblocker_reset() {
                            this->saw_tilde_03_dcblocker_xm1 = 0;
                            this->saw_tilde_03_dcblocker_ym1 = 0;
                        }
                        
                        void saw_tilde_03_dcblocker_dspsetup() {
                            this->saw_tilde_03_dcblocker_reset();
                        }
                        
                        void saw_tilde_03_dspsetup(bool force) {
                            if ((bool)(this->saw_tilde_03_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->saw_tilde_03_setupDone = true;
                            this->saw_tilde_03_dcblocker_dspsetup();
                        }
                        
                        number numbertilde_06_smooth_d_next(number x) {
                            number temp = (number)(x - this->numbertilde_06_smooth_d_prev);
                            this->numbertilde_06_smooth_d_prev = x;
                            return temp;
                        }
                        
                        void numbertilde_06_smooth_d_dspsetup() {
                            this->numbertilde_06_smooth_d_reset();
                        }
                        
                        void numbertilde_06_smooth_d_reset() {
                            this->numbertilde_06_smooth_d_prev = 0;
                        }
                        
                        number numbertilde_06_smooth_next(number x, number up, number down) {
                            if (this->numbertilde_06_smooth_d_next(x) != 0.) {
                                if (x > this->numbertilde_06_smooth_prev) {
                                    number _up = up;
                        
                                    if (_up < 1)
                                        _up = 1;
                        
                                    this->numbertilde_06_smooth_index = _up;
                                    this->numbertilde_06_smooth_increment = (x - this->numbertilde_06_smooth_prev) / _up;
                                } else if (x < this->numbertilde_06_smooth_prev) {
                                    number _down = down;
                        
                                    if (_down < 1)
                                        _down = 1;
                        
                                    this->numbertilde_06_smooth_index = _down;
                                    this->numbertilde_06_smooth_increment = (x - this->numbertilde_06_smooth_prev) / _down;
                                }
                            }
                        
                            if (this->numbertilde_06_smooth_index > 0) {
                                this->numbertilde_06_smooth_prev += this->numbertilde_06_smooth_increment;
                                this->numbertilde_06_smooth_index -= 1;
                            } else {
                                this->numbertilde_06_smooth_prev = x;
                            }
                        
                            return this->numbertilde_06_smooth_prev;
                        }
                        
                        void numbertilde_06_smooth_reset() {
                            this->numbertilde_06_smooth_prev = 0;
                            this->numbertilde_06_smooth_index = 0;
                            this->numbertilde_06_smooth_increment = 0;
                            this->numbertilde_06_smooth_d_reset();
                        }
                        
                        void numbertilde_06_init() {
                            this->numbertilde_06_currentMode = 0;
                        
                            this->getEngine()->sendNumMessage(
                                TAG("setup"),
                                TAG("poly/oscillators/oscC/number~_obj-25"),
                                1,
                                this->_currentTime
                            );
                        }
                        
                        void numbertilde_06_dspsetup(bool force) {
                            if ((bool)(this->numbertilde_06_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->numbertilde_06_currentIntervalInSamples = this->mstosamps(100);
                            this->numbertilde_06_currentInterval = this->numbertilde_06_currentIntervalInSamples;
                            this->numbertilde_06_rampInSamples = this->mstosamps(this->numbertilde_06_ramp);
                            this->numbertilde_06_setupDone = true;
                            this->numbertilde_06_smooth_d_dspsetup();
                        }
                        
                        number tri_tilde_03_dcblocker_next(number x, number gain) {
                            number y = x - this->tri_tilde_03_dcblocker_xm1 + this->tri_tilde_03_dcblocker_ym1 * gain;
                            this->tri_tilde_03_dcblocker_xm1 = x;
                            this->tri_tilde_03_dcblocker_ym1 = y;
                            return y;
                        }
                        
                        void tri_tilde_03_dcblocker_reset() {
                            this->tri_tilde_03_dcblocker_xm1 = 0;
                            this->tri_tilde_03_dcblocker_ym1 = 0;
                        }
                        
                        void tri_tilde_03_dcblocker_dspsetup() {
                            this->tri_tilde_03_dcblocker_reset();
                        }
                        
                        void tri_tilde_03_dspsetup(bool force) {
                            if ((bool)(this->tri_tilde_03_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->tri_tilde_03_setupDone = true;
                            this->tri_tilde_03_dcblocker_dspsetup();
                        }
                        
                        void ip_05_init() {
                            this->ip_05_lastValue = this->ip_05_value;
                        }
                        
                        void ip_05_dspsetup(bool force) {
                            if ((bool)(this->ip_05_setupDone) && (bool)(!(bool)(force)))
                                return;
                        
                            this->ip_05_lastIndex = 0;
                            this->ip_05_setupDone = true;
                        }
                        
                        number rect_tilde_05_rectangle(number phase, number pulsewidth) {
                            if (phase < pulsewidth) {
                                return 1;
                            } else {
                                return -1;
                            }
                        }
                        
                        number rect_tilde_06_rectangle(number phase, number pulsewidth) {
                            if (phase < pulsewidth) {
                                return 1;
                            } else {
                                return -1;
                            }
                        }
                        
                        bool stackprotect_check() {
                            this->stackprotect_count++;
                        
                            if (this->stackprotect_count > 128) {
                                console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                                return true;
                            }
                        
                            return false;
                        }
                        
                        void updateTime(MillisecondTime time) {
                            this->_currentTime = time;
                            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
                        
                            if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
                        
                            if (this->sampleOffsetIntoNextAudioBuffer < 0)
                                this->sampleOffsetIntoNextAudioBuffer = 0;
                        }
                        
                        void assign_defaults()
                        {
                            numberobj_03_value = 0;
                            numberobj_03_value_setter(numberobj_03_value);
                            expr_04_in1 = 0;
                            expr_04_in2 = 1;
                            expr_04_out1 = 0;
                            selector_06_onoff = 1;
                            param_10_value = 2;
                            cycle_tilde_03_frequency = 0;
                            cycle_tilde_03_phase_offset = 0;
                            numbertilde_05_input_number = 0;
                            numbertilde_05_ramp = 0;
                            saw_tilde_03_frequency = 0;
                            saw_tilde_03_syncPhase = 0;
                            numbertilde_06_input_number = 0;
                            numbertilde_06_ramp = 0;
                            tri_tilde_03_frequency = 0;
                            tri_tilde_03_pulsewidth = 0.5;
                            tri_tilde_03_syncPhase = 0;
                            selector_07_onoff = 1;
                            ip_05_value = 0;
                            ip_05_impulse = 0;
                            rect_tilde_05_frequency = 440;
                            rect_tilde_05_pulsewidth = 0.5;
                            rect_tilde_05_syncPhase = 0;
                            rect_tilde_06_frequency = 0;
                            rect_tilde_06_pulsewidth = 0.5;
                            rect_tilde_06_syncPhase = 0;
                            _currentTime = 0;
                            audioProcessSampleCount = 0;
                            sampleOffsetIntoNextAudioBuffer = 0;
                            zeroBuffer = nullptr;
                            dummyBuffer = nullptr;
                            signals[0] = nullptr;
                            signals[1] = nullptr;
                            signals[2] = nullptr;
                            signals[3] = nullptr;
                            signals[4] = nullptr;
                            signals[5] = nullptr;
                            signals[6] = nullptr;
                            signals[7] = nullptr;
                            signals[8] = nullptr;
                            signals[9] = nullptr;
                            signals[10] = nullptr;
                            didAllocateSignals = 0;
                            vs = 0;
                            maxvs = 0;
                            sr = 44100;
                            invsr = 0.00002267573696;
                            numberobj_03_currentFormat = 6;
                            numberobj_03_lastValue = 0;
                            param_10_lastValue = 0;
                            cycle_tilde_03_wrap = 0;
                            cycle_tilde_03_ph_currentPhase = 0;
                            cycle_tilde_03_ph_conv = 0;
                            cycle_tilde_03_setupDone = false;
                            numbertilde_05_currentInterval = 0;
                            numbertilde_05_currentIntervalInSamples = 0;
                            numbertilde_05_lastValue = 0;
                            numbertilde_05_outValue = 0;
                            numbertilde_05_rampInSamples = 0;
                            numbertilde_05_currentMode = 0;
                            numbertilde_05_smooth_d_prev = 0;
                            numbertilde_05_smooth_prev = 0;
                            numbertilde_05_smooth_index = 0;
                            numbertilde_05_smooth_increment = 0;
                            numbertilde_05_setupDone = false;
                            saw_tilde_03_t = 0;
                            saw_tilde_03_lastSyncPhase = 0;
                            saw_tilde_03_lastSyncDiff = 0;
                            saw_tilde_03_didSync = false;
                            saw_tilde_03_dcblocker_xm1 = 0;
                            saw_tilde_03_dcblocker_ym1 = 0;
                            saw_tilde_03_setupDone = false;
                            numbertilde_06_currentInterval = 0;
                            numbertilde_06_currentIntervalInSamples = 0;
                            numbertilde_06_lastValue = 0;
                            numbertilde_06_outValue = 0;
                            numbertilde_06_rampInSamples = 0;
                            numbertilde_06_currentMode = 0;
                            numbertilde_06_smooth_d_prev = 0;
                            numbertilde_06_smooth_prev = 0;
                            numbertilde_06_smooth_index = 0;
                            numbertilde_06_smooth_increment = 0;
                            numbertilde_06_setupDone = false;
                            tri_tilde_03_t = 0;
                            tri_tilde_03_lastSyncPhase = 0;
                            tri_tilde_03_lastSyncDiff = 0;
                            tri_tilde_03_didSync = false;
                            tri_tilde_03_yn = 0;
                            tri_tilde_03_yn1 = 0;
                            tri_tilde_03_yn2 = 0;
                            tri_tilde_03_yn3 = 0;
                            tri_tilde_03_flg = 0;
                            tri_tilde_03_app_correction = 0;
                            tri_tilde_03_dcblocker_xm1 = 0;
                            tri_tilde_03_dcblocker_ym1 = 0;
                            tri_tilde_03_setupDone = false;
                            ip_05_lastIndex = 0;
                            ip_05_lastValue = 0;
                            ip_05_resetCount = 0;
                            ip_05_sigbuf = nullptr;
                            ip_05_setupDone = false;
                            rect_tilde_05_xHistory = 0;
                            rect_tilde_05_yHistory = 0;
                            rect_tilde_05_t = 0;
                            rect_tilde_05_lastSyncPhase = 0;
                            rect_tilde_05_lastSyncDiff = 0;
                            rect_tilde_05_didSync = false;
                            rect_tilde_06_xHistory = 0;
                            rect_tilde_06_yHistory = 0;
                            rect_tilde_06_t = 0;
                            rect_tilde_06_lastSyncPhase = 0;
                            rect_tilde_06_lastSyncDiff = 0;
                            rect_tilde_06_didSync = false;
                            stackprotect_count = 0;
                            _voiceIndex = 0;
                            _noteNumber = 0;
                            isMuted = 1;
                            parameterOffset = 0;
                        }
                        
                        // member variables
                        
                            number numberobj_03_value;
                            number expr_04_in1;
                            number expr_04_in2;
                            number expr_04_out1;
                            number selector_06_onoff;
                            number param_10_value;
                            number cycle_tilde_03_frequency;
                            number cycle_tilde_03_phase_offset;
                            number numbertilde_05_input_number;
                            number numbertilde_05_ramp;
                            number saw_tilde_03_frequency;
                            number saw_tilde_03_syncPhase;
                            number numbertilde_06_input_number;
                            number numbertilde_06_ramp;
                            number tri_tilde_03_frequency;
                            number tri_tilde_03_pulsewidth;
                            number tri_tilde_03_syncPhase;
                            number selector_07_onoff;
                            number ip_05_value;
                            number ip_05_impulse;
                            number rect_tilde_05_frequency;
                            number rect_tilde_05_pulsewidth;
                            number rect_tilde_05_syncPhase;
                            number rect_tilde_06_frequency;
                            number rect_tilde_06_pulsewidth;
                            number rect_tilde_06_syncPhase;
                            MillisecondTime _currentTime;
                            UInt64 audioProcessSampleCount;
                            SampleIndex sampleOffsetIntoNextAudioBuffer;
                            signal zeroBuffer;
                            signal dummyBuffer;
                            SampleValue * signals[11];
                            bool didAllocateSignals;
                            Index vs;
                            Index maxvs;
                            number sr;
                            number invsr;
                            Int numberobj_03_currentFormat;
                            number numberobj_03_lastValue;
                            number param_10_lastValue;
                            UInt noise_tilde_03_state[4] = { };
                            Float64BufferRef cycle_tilde_03_buffer;
                            long cycle_tilde_03_wrap;
                            uint32_t cycle_tilde_03_phasei;
                            SampleValue cycle_tilde_03_f2i;
                            number cycle_tilde_03_ph_currentPhase;
                            number cycle_tilde_03_ph_conv;
                            bool cycle_tilde_03_setupDone;
                            SampleIndex numbertilde_05_currentInterval;
                            SampleIndex numbertilde_05_currentIntervalInSamples;
                            number numbertilde_05_lastValue;
                            number numbertilde_05_outValue;
                            number numbertilde_05_rampInSamples;
                            Int numbertilde_05_currentMode;
                            number numbertilde_05_smooth_d_prev;
                            number numbertilde_05_smooth_prev;
                            number numbertilde_05_smooth_index;
                            number numbertilde_05_smooth_increment;
                            bool numbertilde_05_setupDone;
                            number saw_tilde_03_t;
                            number saw_tilde_03_lastSyncPhase;
                            number saw_tilde_03_lastSyncDiff;
                            bool saw_tilde_03_didSync;
                            number saw_tilde_03_dcblocker_xm1;
                            number saw_tilde_03_dcblocker_ym1;
                            bool saw_tilde_03_setupDone;
                            SampleIndex numbertilde_06_currentInterval;
                            SampleIndex numbertilde_06_currentIntervalInSamples;
                            number numbertilde_06_lastValue;
                            number numbertilde_06_outValue;
                            number numbertilde_06_rampInSamples;
                            Int numbertilde_06_currentMode;
                            number numbertilde_06_smooth_d_prev;
                            number numbertilde_06_smooth_prev;
                            number numbertilde_06_smooth_index;
                            number numbertilde_06_smooth_increment;
                            bool numbertilde_06_setupDone;
                            number tri_tilde_03_t;
                            number tri_tilde_03_lastSyncPhase;
                            number tri_tilde_03_lastSyncDiff;
                            bool tri_tilde_03_didSync;
                            number tri_tilde_03_yn;
                            number tri_tilde_03_yn1;
                            number tri_tilde_03_yn2;
                            number tri_tilde_03_yn3;
                            number tri_tilde_03_flg;
                            number tri_tilde_03_app_correction;
                            number tri_tilde_03_dcblocker_xm1;
                            number tri_tilde_03_dcblocker_ym1;
                            bool tri_tilde_03_setupDone;
                            SampleIndex ip_05_lastIndex;
                            number ip_05_lastValue;
                            SampleIndex ip_05_resetCount;
                            signal ip_05_sigbuf;
                            bool ip_05_setupDone;
                            number rect_tilde_05_xHistory;
                            number rect_tilde_05_yHistory;
                            number rect_tilde_05_t;
                            number rect_tilde_05_lastSyncPhase;
                            number rect_tilde_05_lastSyncDiff;
                            bool rect_tilde_05_didSync;
                            number rect_tilde_06_xHistory;
                            number rect_tilde_06_yHistory;
                            number rect_tilde_06_t;
                            number rect_tilde_06_lastSyncPhase;
                            number rect_tilde_06_lastSyncDiff;
                            bool rect_tilde_06_didSync;
                            number stackprotect_count;
                            Index _voiceIndex;
                            Int _noteNumber;
                            Index isMuted;
                            ParameterIndex parameterOffset;
                        
            };
            
            RNBOSubpatcher_66()
            {
            }
            
            ~RNBOSubpatcher_66()
            {
                delete this->p_05;
                delete this->p_06;
                delete this->p_07;
            }
            
            virtual RNBOSubpatcher_67* getPatcher() const {
                return static_cast<RNBOSubpatcher_67 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
            }
            
            inline number linearinterp(number frac, number x, number y) {
                return x + (y - x) * frac;
            }
            
            ParameterValue fromnormalized(ParameterIndex index, ParameterValue normalizedValue) {
                return this->convertFromNormalizedParameterValue(index, normalizedValue);
            }
            
            Index getNumMidiInputPorts() const {
                return 1;
            }
            
            void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
                this->updateTime(time);
                this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
                this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
                this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
            }
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
                const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
                this->mtof_tilde_01_perform(in1, this->signals[0], n);
                this->ip_06_perform(this->signals[1], n);
                this->dspexpr_03_perform(this->signals[0], this->signals[1], this->signals[2], n);
                this->p_05_perform(this->signals[2], this->zeroBuffer, this->signals[1], this->dummyBuffer, n);
                this->dspexpr_02_perform(this->signals[1], this->dspexpr_02_in2, this->signals[2], n);
                this->ip_07_perform(this->signals[1], n);
                this->dspexpr_05_perform(this->signals[0], this->signals[1], this->signals[3], n);
                this->p_06_perform(this->signals[3], this->zeroBuffer, this->signals[1], this->dummyBuffer, n);
                this->dspexpr_04_perform(this->signals[1], this->dspexpr_04_in2, this->signals[3], n);
                this->dspexpr_06_perform(this->signals[3], this->signals[2], this->signals[1], n);
                this->ip_08_perform(this->signals[2], n);
                this->dspexpr_09_perform(this->signals[0], this->signals[2], this->signals[3], n);
                this->p_07_perform(this->signals[3], this->zeroBuffer, this->signals[2], this->dummyBuffer, n);
                this->dspexpr_08_perform(this->signals[2], this->dspexpr_08_in2, this->signals[3], n);
                this->dspexpr_07_perform(this->signals[1], this->signals[3], out1, n);
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    Index i;
            
                    for (i = 0; i < 4; i++) {
                        this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
                    }
            
                    this->ip_06_sigbuf = resizeSignal(this->ip_06_sigbuf, this->maxvs, maxBlockSize);
                    this->ip_07_sigbuf = resizeSignal(this->ip_07_sigbuf, this->maxvs, maxBlockSize);
                    this->ip_08_sigbuf = resizeSignal(this->ip_08_sigbuf, this->maxvs, maxBlockSize);
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->ip_06_dspsetup(forceDSPSetup);
                this->ip_07_dspsetup(forceDSPSetup);
                this->ip_08_dspsetup(forceDSPSetup);
                this->p_05->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_06->prepareToProcess(sampleRate, maxBlockSize, force);
                this->p_07->prepareToProcess(sampleRate, maxBlockSize, force);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
                this->p_05->setVoiceIndex(index);
                this->p_06->setVoiceIndex(index);
                this->p_07->setVoiceIndex(index);
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
                this->p_05->setNoteNumber(noteNumber);
                this->p_06->setNoteNumber(noteNumber);
                this->p_07->setNoteNumber(noteNumber);
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {
                this->p_05 = new RNBOSubpatcher_61();
                this->p_05->setEngineAndPatcher(this->getEngine(), this);
                this->p_05->initialize();
                this->p_05->setParameterOffset(this->getParameterOffset(this->p_05));
                this->p_06 = new RNBOSubpatcher_62();
                this->p_06->setEngineAndPatcher(this->getEngine(), this);
                this->p_06->initialize();
                this->p_06->setParameterOffset(this->getParameterOffset(this->p_06));
                this->p_07 = new RNBOSubpatcher_63();
                this->p_07->setEngineAndPatcher(this->getEngine(), this);
                this->p_07->initialize();
                this->p_07->setParameterOffset(this->getParameterOffset(this->p_07));
            }
            
            void getPreset(PatcherStateInterface& preset) {
                this->param_11_getPresetValue(getSubState(preset, "levelB"));
                this->param_12_getPresetValue(getSubState(preset, "levelA"));
                this->param_13_getPresetValue(getSubState(preset, "detuneB"));
                this->param_14_getPresetValue(getSubState(preset, "detuneA"));
                this->param_15_getPresetValue(getSubState(preset, "detuneC"));
                this->param_16_getPresetValue(getSubState(preset, "levelC"));
                this->p_05->getPreset(getSubState(getSubState(preset, "__sps"), "oscB"));
                this->p_06->getPreset(getSubState(getSubState(preset, "__sps"), "oscA"));
                this->p_07->getPreset(getSubState(getSubState(preset, "__sps"), "oscC"));
            }
            
            void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
                this->updateTime(time);
            
                switch (index) {
                case 0:
                    {
                    this->param_11_value_set(v);
                    break;
                    }
                case 1:
                    {
                    this->param_12_value_set(v);
                    break;
                    }
                case 2:
                    {
                    this->param_13_value_set(v);
                    break;
                    }
                case 3:
                    {
                    this->param_14_value_set(v);
                    break;
                    }
                case 4:
                    {
                    this->param_15_value_set(v);
                    break;
                    }
                case 5:
                    {
                    this->param_16_value_set(v);
                    break;
                    }
                default:
                    {
                    index -= 6;
            
                    if (index < this->p_05->getNumParameters())
                        this->p_05->setParameterValue(index, v, time);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        this->p_06->setParameterValue(index, v, time);
            
                    index -= this->p_06->getNumParameters();
            
                    if (index < this->p_07->getNumParameters())
                        this->p_07->setParameterValue(index, v, time);
            
                    break;
                    }
                }
            }
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                case 0:
                    {
                    return this->param_11_value;
                    }
                case 1:
                    {
                    return this->param_12_value;
                    }
                case 2:
                    {
                    return this->param_13_value;
                    }
                case 3:
                    {
                    return this->param_14_value;
                    }
                case 4:
                    {
                    return this->param_15_value;
                    }
                case 5:
                    {
                    return this->param_16_value;
                    }
                default:
                    {
                    index -= 6;
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->getParameterValue(index);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->getParameterValue(index);
            
                    index -= this->p_06->getNumParameters();
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->getParameterValue(index);
            
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 6 + this->p_05->getNumParameters() + this->p_06->getNumParameters() + this->p_07->getNumParameters();
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "levelB";
                    }
                case 1:
                    {
                    return "levelA";
                    }
                case 2:
                    {
                    return "detuneB";
                    }
                case 3:
                    {
                    return "detuneA";
                    }
                case 4:
                    {
                    return "detuneC";
                    }
                case 5:
                    {
                    return "levelC";
                    }
                default:
                    {
                    index -= 6;
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->getParameterName(index);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->getParameterName(index);
            
                    index -= this->p_06->getNumParameters();
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->getParameterName(index);
            
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                case 0:
                    {
                    return "poly/oscillators/levelB";
                    }
                case 1:
                    {
                    return "poly/oscillators/levelA";
                    }
                case 2:
                    {
                    return "poly/oscillators/detuneB";
                    }
                case 3:
                    {
                    return "poly/oscillators/detuneA";
                    }
                case 4:
                    {
                    return "poly/oscillators/detuneC";
                    }
                case 5:
                    {
                    return "poly/oscillators/levelC";
                    }
                default:
                    {
                    index -= 6;
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->getParameterId(index);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->getParameterId(index);
            
                    index -= this->p_06->getNumParameters();
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->getParameterId(index);
            
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
                {
                    switch (index) {
                    case 0:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = 0;
                        info->max = 1;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 1:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 1;
                        info->min = 0;
                        info->max = 1;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 2:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = -1000;
                        info->max = 1000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 3:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = -1000;
                        info->max = 1000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 4:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = -1000;
                        info->max = 1000;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    case 5:
                        {
                        info->type = ParameterTypeNumber;
                        info->initialValue = 0;
                        info->min = 0;
                        info->max = 1;
                        info->exponent = 1;
                        info->steps = 0;
                        info->debug = false;
                        info->saveable = true;
                        info->transmittable = true;
                        info->initialized = true;
                        info->visible = true;
                        info->displayName = "";
                        info->unit = "";
                        info->ioType = IOTypeUndefined;
                        info->signalIndex = INVALID_INDEX;
                        break;
                        }
                    default:
                        {
                        index -= 6;
            
                        if (index < this->p_05->getNumParameters())
                            this->p_05->getParameterInfo(index, info);
            
                        index -= this->p_05->getNumParameters();
            
                        if (index < this->p_06->getNumParameters())
                            this->p_06->getParameterInfo(index, info);
            
                        index -= this->p_06->getNumParameters();
            
                        if (index < this->p_07->getNumParameters())
                            this->p_07->getParameterInfo(index, info);
            
                        break;
                        }
                    }
                }
            }
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
                if (subpatcher == this->p_05)
                    return 6;
            
                if (subpatcher == this->p_06)
                    return 6 + this->p_05->getNumParameters();
            
                if (subpatcher == this->p_07)
                    return 6 + this->p_05->getNumParameters() + this->p_06->getNumParameters();
            
                return 0;
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                case 1:
                case 5:
                    {
                    {
                        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                        ParameterValue normalizedValue = (value - 0) / (1 - 0);
                        return normalizedValue;
                    }
                    }
                case 2:
                case 3:
                case 4:
                    {
                    {
                        value = (value < -1000 ? -1000 : (value > 1000 ? 1000 : value));
                        ParameterValue normalizedValue = (value - -1000) / (1000 - -1000);
                        return normalizedValue;
                    }
                    }
                default:
                    {
                    index -= 6;
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->convertToNormalizedParameterValue(index, value);
            
                    index -= this->p_06->getNumParameters();
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->convertToNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                case 0:
                case 1:
                case 5:
                    {
                    {
                        {
                            return 0 + value * (1 - 0);
                        }
                    }
                    }
                case 2:
                case 3:
                case 4:
                    {
                    {
                        {
                            return -1000 + value * (1000 - -1000);
                        }
                    }
                    }
                default:
                    {
                    index -= 6;
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->convertFromNormalizedParameterValue(index, value);
            
                    index -= this->p_06->getNumParameters();
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->convertFromNormalizedParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                case 0:
                    {
                    return this->param_11_value_constrain(value);
                    }
                case 1:
                    {
                    return this->param_12_value_constrain(value);
                    }
                case 2:
                    {
                    return this->param_13_value_constrain(value);
                    }
                case 3:
                    {
                    return this->param_14_value_constrain(value);
                    }
                case 4:
                    {
                    return this->param_15_value_constrain(value);
                    }
                case 5:
                    {
                    return this->param_16_value_constrain(value);
                    }
                default:
                    {
                    index -= 6;
            
                    if (index < this->p_05->getNumParameters())
                        return this->p_05->constrainParameterValue(index, value);
            
                    index -= this->p_05->getNumParameters();
            
                    if (index < this->p_06->getNumParameters())
                        return this->p_06->constrainParameterValue(index, value);
            
                    index -= this->p_06->getNumParameters();
            
                    if (index < this->p_07->getNumParameters())
                        return this->p_07->constrainParameterValue(index, value);
            
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_05->processNumMessage(tag, objectId, time, payload);
                this->p_06->processNumMessage(tag, objectId, time, payload);
                this->p_07->processNumMessage(tag, objectId, time, payload);
            }
            
            void processListMessage(
                MessageTag tag,
                MessageTag objectId,
                MillisecondTime time,
                const list& payload
            ) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_05->processListMessage(tag, objectId, time, payload);
                this->p_06->processListMessage(tag, objectId, time, payload);
                this->p_07->processListMessage(tag, objectId, time, payload);
            }
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                RNBO_UNUSED(objectId);
                this->updateTime(time);
                this->p_05->processBangMessage(tag, objectId, time);
                this->p_06->processBangMessage(tag, objectId, time);
                this->p_07->processBangMessage(tag, objectId, time);
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
            
                }
            
                auto subpatchResult_0 = this->p_05->resolveTag(tag);
            
                if (subpatchResult_0)
                    return subpatchResult_0;
            
                auto subpatchResult_1 = this->p_06->resolveTag(tag);
            
                if (subpatchResult_1)
                    return subpatchResult_1;
            
                auto subpatchResult_2 = this->p_07->resolveTag(tag);
            
                if (subpatchResult_2)
                    return subpatchResult_2;
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->mtof_tilde_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
                }
            
                this->p_05->processDataViewUpdate(index, time);
                this->p_06->processDataViewUpdate(index, time);
                this->p_07->processDataViewUpdate(index, time);
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->mtof_tilde_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
            }
            
            protected:
            
            void param_11_value_set(number v) {
                v = this->param_11_value_constrain(v);
                this->param_11_value = v;
                this->sendParameter(0, false);
            
                if (this->param_11_value != this->param_11_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_11_lastValue = this->param_11_value;
                }
            
                this->dspexpr_02_in2_set(v);
            }
            
            void param_12_value_set(number v) {
                v = this->param_12_value_constrain(v);
                this->param_12_value = v;
                this->sendParameter(1, false);
            
                if (this->param_12_value != this->param_12_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_12_lastValue = this->param_12_value;
                }
            
                this->dspexpr_04_in2_set(v);
            }
            
            void param_13_value_set(number v) {
                v = this->param_13_value_constrain(v);
                this->param_13_value = v;
                this->sendParameter(2, false);
            
                if (this->param_13_value != this->param_13_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_13_lastValue = this->param_13_value;
                }
            
                this->ip_06_value_set(v);
            }
            
            void param_14_value_set(number v) {
                v = this->param_14_value_constrain(v);
                this->param_14_value = v;
                this->sendParameter(3, false);
            
                if (this->param_14_value != this->param_14_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_14_lastValue = this->param_14_value;
                }
            
                this->ip_07_value_set(v);
            }
            
            void param_15_value_set(number v) {
                v = this->param_15_value_constrain(v);
                this->param_15_value = v;
                this->sendParameter(4, false);
            
                if (this->param_15_value != this->param_15_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_15_lastValue = this->param_15_value;
                }
            
                this->ip_08_value_set(v);
            }
            
            void param_16_value_set(number v) {
                v = this->param_16_value_constrain(v);
                this->param_16_value = v;
                this->sendParameter(5, false);
            
                if (this->param_16_value != this->param_16_lastValue) {
                    this->getEngine()->presetTouched();
                    this->param_16_lastValue = this->param_16_value;
                }
            
                this->dspexpr_08_in2_set(v);
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 1;
            }
            
            Index getNumOutputChannels() const {
                return 1;
            }
            
            void initializeObjects() {
                this->mtof_tilde_01_innerScala_init();
                this->mtof_tilde_01_init();
                this->ip_06_init();
                this->ip_07_init();
                this->ip_08_init();
                this->p_05->initializeObjects();
                this->p_06->initializeObjects();
                this->p_07->initializeObjects();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->p_05->startup();
                this->p_06->startup();
                this->p_07->startup();
            
                {
                    this->scheduleParamInit(0, 0);
                }
            
                {
                    this->scheduleParamInit(1, 0);
                }
            
                {
                    this->scheduleParamInit(2, 0);
                }
            
                {
                    this->scheduleParamInit(3, 0);
                }
            
                {
                    this->scheduleParamInit(4, 0);
                }
            
                {
                    this->scheduleParamInit(5, 0);
                }
            }
            
            void allocateDataRefs() {
                this->p_05->allocateDataRefs();
                this->p_06->allocateDataRefs();
                this->p_07->allocateDataRefs();
                this->mtof_tilde_01_innerMtoF_buffer->requestSize(65536, 1);
                this->mtof_tilde_01_innerMtoF_buffer->setSampleRate(this->sr);
                this->mtof_tilde_01_innerMtoF_buffer = this->mtof_tilde_01_innerMtoF_buffer->allocateIfNeeded();
            }
            
            number param_11_value_constrain(number v) const {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void dspexpr_02_in2_set(number v) {
                this->dspexpr_02_in2 = v;
            }
            
            number param_12_value_constrain(number v) const {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void dspexpr_04_in2_set(number v) {
                this->dspexpr_04_in2 = v;
            }
            
            number param_13_value_constrain(number v) const {
                v = (v > 1000 ? 1000 : (v < -1000 ? -1000 : v));
                return v;
            }
            
            void ip_06_value_set(number v) {
                this->ip_06_value = v;
                this->ip_06_fillSigBuf();
                this->ip_06_lastValue = v;
            }
            
            number param_14_value_constrain(number v) const {
                v = (v > 1000 ? 1000 : (v < -1000 ? -1000 : v));
                return v;
            }
            
            void ip_07_value_set(number v) {
                this->ip_07_value = v;
                this->ip_07_fillSigBuf();
                this->ip_07_lastValue = v;
            }
            
            number param_15_value_constrain(number v) const {
                v = (v > 1000 ? 1000 : (v < -1000 ? -1000 : v));
                return v;
            }
            
            void ip_08_value_set(number v) {
                this->ip_08_value = v;
                this->ip_08_fillSigBuf();
                this->ip_08_lastValue = v;
            }
            
            number param_16_value_constrain(number v) const {
                v = (v > 1 ? 1 : (v < 0 ? 0 : v));
                return v;
            }
            
            void dspexpr_08_in2_set(number v) {
                this->dspexpr_08_in2 = v;
            }
            
            void ctlin_01_outchannel_set(number ) {}
            
            void ctlin_01_outcontroller_set(number ) {}
            
            void fromnormalized_01_output_set(number v) {
                this->param_11_value_set(v);
            }
            
            void fromnormalized_01_input_set(number v) {
                this->fromnormalized_01_output_set(this->fromnormalized(0, v));
            }
            
            void expr_05_out1_set(number v) {
                this->expr_05_out1 = v;
                this->fromnormalized_01_input_set(this->expr_05_out1);
            }
            
            void expr_05_in1_set(number in1) {
                this->expr_05_in1 = in1;
                this->expr_05_out1_set(this->expr_05_in1 * this->expr_05_in2);//#map:expr_05:1
            }
            
            void ctlin_01_value_set(number v) {
                this->expr_05_in1_set(v);
            }
            
            void ctlin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
                RNBO_UNUSED(length);
                RNBO_UNUSED(port);
            
                if (status == 0xB0 && (channel == this->ctlin_01_channel || this->ctlin_01_channel == -1) && (data[1] == this->ctlin_01_controller || this->ctlin_01_controller == -1)) {
                    this->ctlin_01_outchannel_set(channel);
                    this->ctlin_01_outcontroller_set(data[1]);
                    this->ctlin_01_value_set(data[2]);
                    this->ctlin_01_status = 0;
                }
            }
            
            void ctlin_02_outchannel_set(number ) {}
            
            void ctlin_02_outcontroller_set(number ) {}
            
            void fromnormalized_02_output_set(number v) {
                this->param_12_value_set(v);
            }
            
            void fromnormalized_02_input_set(number v) {
                this->fromnormalized_02_output_set(this->fromnormalized(1, v));
            }
            
            void expr_06_out1_set(number v) {
                this->expr_06_out1 = v;
                this->fromnormalized_02_input_set(this->expr_06_out1);
            }
            
            void expr_06_in1_set(number in1) {
                this->expr_06_in1 = in1;
                this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:expr_06:1
            }
            
            void ctlin_02_value_set(number v) {
                this->expr_06_in1_set(v);
            }
            
            void ctlin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
                RNBO_UNUSED(length);
                RNBO_UNUSED(port);
            
                if (status == 0xB0 && (channel == this->ctlin_02_channel || this->ctlin_02_channel == -1) && (data[1] == this->ctlin_02_controller || this->ctlin_02_controller == -1)) {
                    this->ctlin_02_outchannel_set(channel);
                    this->ctlin_02_outcontroller_set(data[1]);
                    this->ctlin_02_value_set(data[2]);
                    this->ctlin_02_status = 0;
                }
            }
            
            void ctlin_03_outchannel_set(number ) {}
            
            void ctlin_03_outcontroller_set(number ) {}
            
            void fromnormalized_03_output_set(number v) {
                this->param_16_value_set(v);
            }
            
            void fromnormalized_03_input_set(number v) {
                this->fromnormalized_03_output_set(this->fromnormalized(5, v));
            }
            
            void expr_07_out1_set(number v) {
                this->expr_07_out1 = v;
                this->fromnormalized_03_input_set(this->expr_07_out1);
            }
            
            void expr_07_in1_set(number in1) {
                this->expr_07_in1 = in1;
                this->expr_07_out1_set(this->expr_07_in1 * this->expr_07_in2);//#map:expr_07:1
            }
            
            void ctlin_03_value_set(number v) {
                this->expr_07_in1_set(v);
            }
            
            void ctlin_03_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
                RNBO_UNUSED(length);
                RNBO_UNUSED(port);
            
                if (status == 0xB0 && (channel == this->ctlin_03_channel || this->ctlin_03_channel == -1) && (data[1] == this->ctlin_03_controller || this->ctlin_03_controller == -1)) {
                    this->ctlin_03_outchannel_set(channel);
                    this->ctlin_03_outcontroller_set(data[1]);
                    this->ctlin_03_value_set(data[2]);
                    this->ctlin_03_status = 0;
                }
            }
            
            void mtof_tilde_01_perform(const Sample * midivalue, SampleValue * out, Index n) {
                auto __mtof_tilde_01_base = this->mtof_tilde_01_base;
            
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = this->mtof_tilde_01_innerMtoF_next(midivalue[(Index)i], __mtof_tilde_01_base);
                }
            }
            
            void ip_06_perform(SampleValue * out, Index n) {
                auto __ip_06_lastValue = this->ip_06_lastValue;
                auto __ip_06_lastIndex = this->ip_06_lastIndex;
            
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = ((SampleIndex)(i) >= __ip_06_lastIndex ? __ip_06_lastValue : this->ip_06_sigbuf[(Index)i]);
                }
            
                __ip_06_lastIndex = 0;
                this->ip_06_lastIndex = __ip_06_lastIndex;
            }
            
            void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void p_05_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                // subpatcher: oscB
                ConstSampleArray<2> ins = {in1, in2};
            
                SampleArray<2> outs = {out1, out2};
                this->p_05->process(ins, 2, outs, 2, n);
            }
            
            void dspexpr_02_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
                }
            }
            
            void ip_07_perform(SampleValue * out, Index n) {
                auto __ip_07_lastValue = this->ip_07_lastValue;
                auto __ip_07_lastIndex = this->ip_07_lastIndex;
            
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = ((SampleIndex)(i) >= __ip_07_lastIndex ? __ip_07_lastValue : this->ip_07_sigbuf[(Index)i]);
                }
            
                __ip_07_lastIndex = 0;
                this->ip_07_lastIndex = __ip_07_lastIndex;
            }
            
            void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void p_06_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                // subpatcher: oscA
                ConstSampleArray<2> ins = {in1, in2};
            
                SampleArray<2> outs = {out1, out2};
                this->p_06->process(ins, 2, outs, 2, n);
            }
            
            void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void ip_08_perform(SampleValue * out, Index n) {
                auto __ip_08_lastValue = this->ip_08_lastValue;
                auto __ip_08_lastIndex = this->ip_08_lastIndex;
            
                for (Index i = 0; i < n; i++) {
                    out[(Index)i] = ((SampleIndex)(i) >= __ip_08_lastIndex ? __ip_08_lastValue : this->ip_08_sigbuf[(Index)i]);
                }
            
                __ip_08_lastIndex = 0;
                this->ip_08_lastIndex = __ip_08_lastIndex;
            }
            
            void dspexpr_09_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void p_07_perform(
                const SampleValue * in1,
                const SampleValue * in2,
                SampleValue * out1,
                SampleValue * out2,
                Index n
            ) {
                // subpatcher: oscC
                ConstSampleArray<2> ins = {in1, in2};
            
                SampleArray<2> outs = {out1, out2};
                this->p_07->process(ins, 2, outs, 2, n);
            }
            
            void dspexpr_08_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
                }
            }
            
            void dspexpr_07_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
                Index i;
            
                for (i = 0; i < n; i++) {
                    out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number mtof_tilde_01_innerMtoF_next(number midivalue, number tuning) {
                if (midivalue == this->mtof_tilde_01_innerMtoF_lastInValue && tuning == this->mtof_tilde_01_innerMtoF_lastTuning)
                    return this->mtof_tilde_01_innerMtoF_lastOutValue;
            
                this->mtof_tilde_01_innerMtoF_lastInValue = midivalue;
                this->mtof_tilde_01_innerMtoF_lastTuning = tuning;
                number result = 0;
            
                {
                    result = rnbo_exp(.057762265 * (midivalue - 69.0));
                }
            
                this->mtof_tilde_01_innerMtoF_lastOutValue = tuning * result;
                return this->mtof_tilde_01_innerMtoF_lastOutValue;
            }
            
            void mtof_tilde_01_innerMtoF_reset() {
                this->mtof_tilde_01_innerMtoF_lastInValue = 0;
                this->mtof_tilde_01_innerMtoF_lastOutValue = 0;
                this->mtof_tilde_01_innerMtoF_lastTuning = 0;
            }
            
            void mtof_tilde_01_innerScala_mid(int v) {
                this->mtof_tilde_01_innerScala_kbmMid = v;
                this->mtof_tilde_01_innerScala_updateRefFreq();
            }
            
            void mtof_tilde_01_innerScala_ref(int v) {
                this->mtof_tilde_01_innerScala_kbmRefNum = v;
                this->mtof_tilde_01_innerScala_updateRefFreq();
            }
            
            void mtof_tilde_01_innerScala_base(number v) {
                this->mtof_tilde_01_innerScala_kbmRefFreq = v;
                this->mtof_tilde_01_innerScala_updateRefFreq();
            }
            
            void mtof_tilde_01_innerScala_init() {
                list sclValid = {
                    12,
                    100,
                    0,
                    200,
                    0,
                    300,
                    0,
                    400,
                    0,
                    500,
                    0,
                    600,
                    0,
                    700,
                    0,
                    800,
                    0,
                    900,
                    0,
                    1000,
                    0,
                    1100,
                    0,
                    2,
                    1
                };
            
                this->mtof_tilde_01_innerScala_updateScale(sclValid);
            }
            
            void mtof_tilde_01_innerScala_update(list scale, list map) {
                if (scale->length > 0) {
                    this->mtof_tilde_01_innerScala_updateScale(scale);
                }
            
                if (map->length > 0) {
                    this->mtof_tilde_01_innerScala_updateMap(map);
                }
            }
            
            number mtof_tilde_01_innerScala_mtof(number note) {
                if ((bool)(this->mtof_tilde_01_innerScala_lastValid) && this->mtof_tilde_01_innerScala_lastNote == note) {
                    return this->mtof_tilde_01_innerScala_lastFreq;
                }
            
                array<int, 2> degoct = this->mtof_tilde_01_innerScala_applyKBM(note);
                number out = 0;
            
                if (degoct[1] > 0) {
                    out = this->mtof_tilde_01_innerScala_applySCL(degoct[0], fract(note), this->mtof_tilde_01_innerScala_refFreq);
                }
            
                this->mtof_tilde_01_innerScala_updateLast(note, out);
                return out;
            }
            
            number mtof_tilde_01_innerScala_ftom(number hz) {
                if (hz <= 0.0) {
                    return 0.0;
                }
            
                if ((bool)(this->mtof_tilde_01_innerScala_lastValid) && this->mtof_tilde_01_innerScala_lastFreq == hz) {
                    return this->mtof_tilde_01_innerScala_lastNote;
                }
            
                array<number, 2> df = this->mtof_tilde_01_innerScala_hztodeg(hz);
                int degree = (int)(df[0]);
                number frac = df[1];
                number out = 0;
            
                if (this->mtof_tilde_01_innerScala_kbmSize == 0) {
                    out = this->mtof_tilde_01_innerScala_kbmMid + degree;
                } else {
                    array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_kbmOctaveDegree);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
                    Index entry = 0;
            
                    for (Index i = 0; i < this->mtof_tilde_01_innerScala_kbmMapSize; i++) {
                        if (index == this->mtof_tilde_01_innerScala_kbmValid[(Index)(i + this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET)]) {
                            entry = i;
                            break;
                        }
                    }
            
                    out = oct * this->mtof_tilde_01_innerScala_kbmSize + entry + this->mtof_tilde_01_innerScala_kbmMid;
                }
            
                out = out + frac;
                this->mtof_tilde_01_innerScala_updateLast(out, hz);
                return this->mtof_tilde_01_innerScala_lastNote;
            }
            
            int mtof_tilde_01_innerScala_updateScale(list scl) {
                if (scl->length < 1) {
                    return 0;
                }
            
                number sclDataEntries = scl[0] * 2 + 1;
            
                if (sclDataEntries <= scl->length) {
                    this->mtof_tilde_01_innerScala_lastValid = false;
                    this->mtof_tilde_01_innerScala_sclExpMul = {};
                    number last = 1;
            
                    for (Index i = 1; i < sclDataEntries; i += 2) {
                        const number c = (const number)(scl[(Index)(i + 0)]);
                        const number d = (const number)(scl[(Index)(i + 1)]);
            
                        if (d <= 0) {
                            last = c / (number)1200;
                        } else {
                            last = rnbo_log2(c / d);
                        }
            
                        this->mtof_tilde_01_innerScala_sclExpMul->push(last);
                    }
            
                    this->mtof_tilde_01_innerScala_sclOctaveMul = last;
                    this->mtof_tilde_01_innerScala_sclEntryCount = (int)(this->mtof_tilde_01_innerScala_sclExpMul->length);
            
                    if (scl->length >= sclDataEntries + 3) {
                        this->mtof_tilde_01_innerScala_kbmMid = (int)(scl[(Index)(sclDataEntries + 2)]);
                        this->mtof_tilde_01_innerScala_kbmRefNum = (int)(scl[(Index)(sclDataEntries + 1)]);
                        this->mtof_tilde_01_innerScala_kbmRefFreq = scl[(Index)(sclDataEntries + 0)];
                        this->mtof_tilde_01_innerScala_kbmSize = (int)(0);
                    }
            
                    this->mtof_tilde_01_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            int mtof_tilde_01_innerScala_updateMap(list kbm) {
                if (kbm->length == 1 && kbm[0] == 0.0) {
                    kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
                }
            
                if (kbm->length >= 6 && kbm[0] >= 0.0) {
                    this->mtof_tilde_01_innerScala_lastValid = false;
                    Index size = (Index)(kbm[0]);
                    int octave = 12;
            
                    if (kbm->length > 6) {
                        octave = (int)(kbm[6]);
                    }
            
                    if (size > 0 && kbm->length < this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET) {
                        return 0;
                    }
            
                    this->mtof_tilde_01_innerScala_kbmSize = (int)(size);
                    this->mtof_tilde_01_innerScala_kbmMin = (int)(kbm[1]);
                    this->mtof_tilde_01_innerScala_kbmMax = (int)(kbm[2]);
                    this->mtof_tilde_01_innerScala_kbmMid = (int)(kbm[3]);
                    this->mtof_tilde_01_innerScala_kbmRefNum = (int)(kbm[4]);
                    this->mtof_tilde_01_innerScala_kbmRefFreq = kbm[5];
                    this->mtof_tilde_01_innerScala_kbmOctaveDegree = octave;
                    this->mtof_tilde_01_innerScala_kbmValid = kbm;
                    this->mtof_tilde_01_innerScala_kbmMapSize = (kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET > kbm->length ? kbm->length : (kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET < 0 ? 0 : kbm->length - this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET));
                    this->mtof_tilde_01_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            void mtof_tilde_01_innerScala_updateLast(number note, number freq) {
                this->mtof_tilde_01_innerScala_lastValid = true;
                this->mtof_tilde_01_innerScala_lastNote = note;
                this->mtof_tilde_01_innerScala_lastFreq = freq;
            }
            
            array<number, 2> mtof_tilde_01_innerScala_hztodeg(number hz) {
                number hza = rnbo_abs(hz);
            
                number octave = rnbo_floor(
                    rnbo_log2(hza / this->mtof_tilde_01_innerScala_refFreq) / this->mtof_tilde_01_innerScala_sclOctaveMul
                );
            
                int i = 0;
                number frac = 0;
                number n = 0;
            
                for (; i < this->mtof_tilde_01_innerScala_sclEntryCount; i++) {
                    number c = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->mtof_tilde_01_innerScala_refFreq);
                    n = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->mtof_tilde_01_innerScala_refFreq);
            
                    if (c <= hza && hza < n) {
                        if (c != hza) {
                            frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                        }
            
                        break;
                    }
                }
            
                if (i == this->mtof_tilde_01_innerScala_sclEntryCount && n != hza) {
                    number c = n;
                    n = this->mtof_tilde_01_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->mtof_tilde_01_innerScala_refFreq);
                    frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                }
            
                number deg = i + octave * this->mtof_tilde_01_innerScala_sclEntryCount;
            
                {
                    deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
                    frac = 0.0;
                }
            
                return {deg, frac};
            }
            
            array<int, 2> mtof_tilde_01_innerScala_octdegree(int degree, int count) {
                int octave = 0;
                int index = 0;
            
                if (degree < 0) {
                    octave = -(1 + (-1 - degree) / count);
                    index = -degree % count;
            
                    if (index > 0) {
                        index = count - index;
                    }
                } else {
                    octave = degree / count;
                    index = degree % count;
                }
            
                return {octave, index};
            }
            
            array<int, 2> mtof_tilde_01_innerScala_applyKBM(number note) {
                if ((this->mtof_tilde_01_innerScala_kbmMin == this->mtof_tilde_01_innerScala_kbmMax && this->mtof_tilde_01_innerScala_kbmMax == 0) || (note >= this->mtof_tilde_01_innerScala_kbmMin && note <= this->mtof_tilde_01_innerScala_kbmMax)) {
                    int degree = (int)(rnbo_floor(note - this->mtof_tilde_01_innerScala_kbmMid));
            
                    if (this->mtof_tilde_01_innerScala_kbmSize == 0) {
                        return {degree, 1};
                    }
            
                    array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_kbmSize);
                    int octave = (int)(octdeg[0]);
                    Index index = (Index)(octdeg[1]);
            
                    if (this->mtof_tilde_01_innerScala_kbmMapSize > index) {
                        degree = (int)(this->mtof_tilde_01_innerScala_kbmValid[(Index)(this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET + index)]);
            
                        if (degree >= 0) {
                            return {degree + octave * this->mtof_tilde_01_innerScala_kbmOctaveDegree, 1};
                        }
                    }
                }
            
                return {-1, 0};
            }
            
            number mtof_tilde_01_innerScala_applySCL(int degree, number frac, number refFreq) {
                array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(degree, this->mtof_tilde_01_innerScala_sclEntryCount);
                return this->mtof_tilde_01_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
            }
            
            number mtof_tilde_01_innerScala_applySCLOctIndex(number octave, int index, number frac, number refFreq) {
                number p = 0;
            
                if (index > 0) {
                    p = this->mtof_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
                }
            
                if (frac > 0) {
                    p = this->linearinterp(frac, p, this->mtof_tilde_01_innerScala_sclExpMul[(Index)index]);
                } else if (frac < 0) {
                    p = this->linearinterp(-frac, this->mtof_tilde_01_innerScala_sclExpMul[(Index)index], p);
                }
            
                return refFreq * rnbo_pow(2, p + octave * this->mtof_tilde_01_innerScala_sclOctaveMul);
            }
            
            void mtof_tilde_01_innerScala_updateRefFreq() {
                this->mtof_tilde_01_innerScala_lastValid = false;
                int refOffset = (int)(this->mtof_tilde_01_innerScala_kbmRefNum - this->mtof_tilde_01_innerScala_kbmMid);
            
                if (refOffset == 0) {
                    this->mtof_tilde_01_innerScala_refFreq = this->mtof_tilde_01_innerScala_kbmRefFreq;
                } else {
                    int base = (int)(this->mtof_tilde_01_innerScala_kbmSize);
            
                    if (base < 1) {
                        base = this->mtof_tilde_01_innerScala_sclEntryCount;
                    }
            
                    array<int, 2> octdeg = this->mtof_tilde_01_innerScala_octdegree(refOffset, base);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
            
                    if (base > 0) {
                        oct = oct + rnbo_floor(index / base);
                        index = index % base;
                    }
            
                    if (index >= 0 && index < this->mtof_tilde_01_innerScala_kbmSize) {
                        if (index < this->mtof_tilde_01_innerScala_kbmMapSize) {
                            index = (int)(this->mtof_tilde_01_innerScala_kbmValid[(Index)((Index)(index) + this->mtof_tilde_01_innerScala_KBM_MAP_OFFSET)]);
                        } else {
                            index = -1;
                        }
                    }
            
                    if (index < 0 || index > this->mtof_tilde_01_innerScala_sclExpMul->length)
                        {} else {
                        number p = 0;
            
                        if (index > 0) {
                            p = this->mtof_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
                        }
            
                        this->mtof_tilde_01_innerScala_refFreq = this->mtof_tilde_01_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->mtof_tilde_01_innerScala_sclOctaveMul);
                    }
                }
            }
            
            void mtof_tilde_01_innerScala_reset() {
                this->mtof_tilde_01_innerScala_lastValid = false;
                this->mtof_tilde_01_innerScala_lastNote = 0;
                this->mtof_tilde_01_innerScala_lastFreq = 0;
                this->mtof_tilde_01_innerScala_sclEntryCount = 0;
                this->mtof_tilde_01_innerScala_sclOctaveMul = 1;
                this->mtof_tilde_01_innerScala_sclExpMul = {};
                this->mtof_tilde_01_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
                this->mtof_tilde_01_innerScala_kbmMid = 60;
                this->mtof_tilde_01_innerScala_kbmRefNum = 69;
                this->mtof_tilde_01_innerScala_kbmRefFreq = 440;
                this->mtof_tilde_01_innerScala_kbmSize = 0;
                this->mtof_tilde_01_innerScala_kbmMin = 0;
                this->mtof_tilde_01_innerScala_kbmMax = 0;
                this->mtof_tilde_01_innerScala_kbmOctaveDegree = 12;
                this->mtof_tilde_01_innerScala_kbmMapSize = 0;
                this->mtof_tilde_01_innerScala_refFreq = 261.63;
            }
            
            void mtof_tilde_01_init() {
                this->mtof_tilde_01_innerScala_update(this->mtof_tilde_01_scale, this->mtof_tilde_01_map);
            }
            
            void param_11_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_11_value;
            }
            
            void param_11_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_11_value_set(preset["value"]);
            }
            
            void ip_06_init() {
                this->ip_06_lastValue = this->ip_06_value;
            }
            
            void ip_06_fillSigBuf() {
                if ((bool)(this->ip_06_sigbuf)) {
                    SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
            
                    if (k >= (SampleIndex)(this->vs))
                        k = (SampleIndex)(this->vs) - 1;
            
                    for (SampleIndex i = (SampleIndex)(this->ip_06_lastIndex); i < k; i++) {
                        if (this->ip_06_resetCount > 0) {
                            this->ip_06_sigbuf[(Index)i] = 1;
                            this->ip_06_resetCount--;
                        } else {
                            this->ip_06_sigbuf[(Index)i] = this->ip_06_lastValue;
                        }
                    }
            
                    this->ip_06_lastIndex = k;
                }
            }
            
            void ip_06_dspsetup(bool force) {
                if ((bool)(this->ip_06_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->ip_06_lastIndex = 0;
                this->ip_06_setupDone = true;
            }
            
            void ip_07_init() {
                this->ip_07_lastValue = this->ip_07_value;
            }
            
            void ip_07_fillSigBuf() {
                if ((bool)(this->ip_07_sigbuf)) {
                    SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
            
                    if (k >= (SampleIndex)(this->vs))
                        k = (SampleIndex)(this->vs) - 1;
            
                    for (SampleIndex i = (SampleIndex)(this->ip_07_lastIndex); i < k; i++) {
                        if (this->ip_07_resetCount > 0) {
                            this->ip_07_sigbuf[(Index)i] = 1;
                            this->ip_07_resetCount--;
                        } else {
                            this->ip_07_sigbuf[(Index)i] = this->ip_07_lastValue;
                        }
                    }
            
                    this->ip_07_lastIndex = k;
                }
            }
            
            void ip_07_dspsetup(bool force) {
                if ((bool)(this->ip_07_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->ip_07_lastIndex = 0;
                this->ip_07_setupDone = true;
            }
            
            void param_12_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_12_value;
            }
            
            void param_12_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_12_value_set(preset["value"]);
            }
            
            void param_13_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_13_value;
            }
            
            void param_13_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_13_value_set(preset["value"]);
            }
            
            void param_14_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_14_value;
            }
            
            void param_14_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_14_value_set(preset["value"]);
            }
            
            void ip_08_init() {
                this->ip_08_lastValue = this->ip_08_value;
            }
            
            void ip_08_fillSigBuf() {
                if ((bool)(this->ip_08_sigbuf)) {
                    SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
            
                    if (k >= (SampleIndex)(this->vs))
                        k = (SampleIndex)(this->vs) - 1;
            
                    for (SampleIndex i = (SampleIndex)(this->ip_08_lastIndex); i < k; i++) {
                        if (this->ip_08_resetCount > 0) {
                            this->ip_08_sigbuf[(Index)i] = 1;
                            this->ip_08_resetCount--;
                        } else {
                            this->ip_08_sigbuf[(Index)i] = this->ip_08_lastValue;
                        }
                    }
            
                    this->ip_08_lastIndex = k;
                }
            }
            
            void ip_08_dspsetup(bool force) {
                if ((bool)(this->ip_08_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->ip_08_lastIndex = 0;
                this->ip_08_setupDone = true;
            }
            
            void param_15_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_15_value;
            }
            
            void param_15_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_15_value_set(preset["value"]);
            }
            
            void param_16_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->param_16_value;
            }
            
            void param_16_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->param_16_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                dspexpr_02_in1 = 0;
                dspexpr_02_in2 = 1;
                dspexpr_03_in1 = 0;
                dspexpr_03_in2 = 0;
                dspexpr_04_in1 = 0;
                dspexpr_04_in2 = 1;
                dspexpr_05_in1 = 0;
                dspexpr_05_in2 = 0;
                mtof_tilde_01_midivalue = 0;
                mtof_tilde_01_base = 440;
                p_05_target = 0;
                p_06_target = 0;
                param_11_value = 0;
                ip_06_value = 0;
                ip_06_impulse = 0;
                ip_07_value = 0;
                ip_07_impulse = 0;
                param_12_value = 1;
                param_13_value = 0;
                param_14_value = 0;
                dspexpr_06_in1 = 0;
                dspexpr_06_in2 = 0;
                dspexpr_07_in1 = 0;
                dspexpr_07_in2 = 0;
                dspexpr_08_in1 = 0;
                dspexpr_08_in2 = 1;
                dspexpr_09_in1 = 0;
                dspexpr_09_in2 = 0;
                p_07_target = 0;
                ip_08_value = 0;
                ip_08_impulse = 0;
                param_15_value = 0;
                param_16_value = 0;
                ctlin_01_input = 0;
                ctlin_01_controller = 75;
                ctlin_01_channel = -1;
                expr_05_in1 = 0;
                expr_05_in2 = 0.007874015748;
                expr_05_out1 = 0;
                ctlin_02_input = 0;
                ctlin_02_controller = 74;
                ctlin_02_channel = -1;
                expr_06_in1 = 0;
                expr_06_in2 = 0.007874015748;
                expr_06_out1 = 0;
                ctlin_03_input = 0;
                ctlin_03_controller = 76;
                ctlin_03_channel = -1;
                expr_07_in1 = 0;
                expr_07_in2 = 0.007874015748;
                expr_07_out1 = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                signals[0] = nullptr;
                signals[1] = nullptr;
                signals[2] = nullptr;
                signals[3] = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                mtof_tilde_01_innerMtoF_lastInValue = 0;
                mtof_tilde_01_innerMtoF_lastOutValue = 0;
                mtof_tilde_01_innerMtoF_lastTuning = 0;
                mtof_tilde_01_innerScala_lastValid = false;
                mtof_tilde_01_innerScala_lastNote = 0;
                mtof_tilde_01_innerScala_lastFreq = 0;
                mtof_tilde_01_innerScala_sclEntryCount = 0;
                mtof_tilde_01_innerScala_sclOctaveMul = 1;
                mtof_tilde_01_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
                mtof_tilde_01_innerScala_kbmMid = 60;
                mtof_tilde_01_innerScala_kbmRefNum = 69;
                mtof_tilde_01_innerScala_kbmRefFreq = 440;
                mtof_tilde_01_innerScala_kbmSize = 0;
                mtof_tilde_01_innerScala_kbmMin = 0;
                mtof_tilde_01_innerScala_kbmMax = 0;
                mtof_tilde_01_innerScala_kbmOctaveDegree = 12;
                mtof_tilde_01_innerScala_kbmMapSize = 0;
                mtof_tilde_01_innerScala_refFreq = 261.63;
                param_11_lastValue = 0;
                ip_06_lastIndex = 0;
                ip_06_lastValue = 0;
                ip_06_resetCount = 0;
                ip_06_sigbuf = nullptr;
                ip_06_setupDone = false;
                ip_07_lastIndex = 0;
                ip_07_lastValue = 0;
                ip_07_resetCount = 0;
                ip_07_sigbuf = nullptr;
                ip_07_setupDone = false;
                param_12_lastValue = 0;
                param_13_lastValue = 0;
                param_14_lastValue = 0;
                ip_08_lastIndex = 0;
                ip_08_lastValue = 0;
                ip_08_resetCount = 0;
                ip_08_sigbuf = nullptr;
                ip_08_setupDone = false;
                param_15_lastValue = 0;
                param_16_lastValue = 0;
                ctlin_01_status = 0;
                ctlin_01_byte1 = -1;
                ctlin_01_inchan = 0;
                ctlin_02_status = 0;
                ctlin_02_byte1 = -1;
                ctlin_02_inchan = 0;
                ctlin_03_status = 0;
                ctlin_03_byte1 = -1;
                ctlin_03_inchan = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number dspexpr_02_in1;
                number dspexpr_02_in2;
                number dspexpr_03_in1;
                number dspexpr_03_in2;
                number dspexpr_04_in1;
                number dspexpr_04_in2;
                number dspexpr_05_in1;
                number dspexpr_05_in2;
                number mtof_tilde_01_midivalue;
                list mtof_tilde_01_scale;
                list mtof_tilde_01_map;
                number mtof_tilde_01_base;
                number p_05_target;
                number p_06_target;
                number param_11_value;
                number ip_06_value;
                number ip_06_impulse;
                number ip_07_value;
                number ip_07_impulse;
                number param_12_value;
                number param_13_value;
                number param_14_value;
                number dspexpr_06_in1;
                number dspexpr_06_in2;
                number dspexpr_07_in1;
                number dspexpr_07_in2;
                number dspexpr_08_in1;
                number dspexpr_08_in2;
                number dspexpr_09_in1;
                number dspexpr_09_in2;
                number p_07_target;
                number ip_08_value;
                number ip_08_impulse;
                number param_15_value;
                number param_16_value;
                number ctlin_01_input;
                number ctlin_01_controller;
                number ctlin_01_channel;
                number expr_05_in1;
                number expr_05_in2;
                number expr_05_out1;
                number ctlin_02_input;
                number ctlin_02_controller;
                number ctlin_02_channel;
                number expr_06_in1;
                number expr_06_in2;
                number expr_06_out1;
                number ctlin_03_input;
                number ctlin_03_controller;
                number ctlin_03_channel;
                number expr_07_in1;
                number expr_07_in2;
                number expr_07_out1;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                SampleValue * signals[4];
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number mtof_tilde_01_innerMtoF_lastInValue;
                number mtof_tilde_01_innerMtoF_lastOutValue;
                number mtof_tilde_01_innerMtoF_lastTuning;
                Float64BufferRef mtof_tilde_01_innerMtoF_buffer;
                const Index mtof_tilde_01_innerScala_KBM_MAP_OFFSET = 7;
                bool mtof_tilde_01_innerScala_lastValid;
                number mtof_tilde_01_innerScala_lastNote;
                number mtof_tilde_01_innerScala_lastFreq;
                int mtof_tilde_01_innerScala_sclEntryCount;
                number mtof_tilde_01_innerScala_sclOctaveMul;
                list mtof_tilde_01_innerScala_sclExpMul;
                list mtof_tilde_01_innerScala_kbmValid;
                int mtof_tilde_01_innerScala_kbmMid;
                int mtof_tilde_01_innerScala_kbmRefNum;
                number mtof_tilde_01_innerScala_kbmRefFreq;
                int mtof_tilde_01_innerScala_kbmSize;
                int mtof_tilde_01_innerScala_kbmMin;
                int mtof_tilde_01_innerScala_kbmMax;
                int mtof_tilde_01_innerScala_kbmOctaveDegree;
                Index mtof_tilde_01_innerScala_kbmMapSize;
                number mtof_tilde_01_innerScala_refFreq;
                number param_11_lastValue;
                SampleIndex ip_06_lastIndex;
                number ip_06_lastValue;
                SampleIndex ip_06_resetCount;
                signal ip_06_sigbuf;
                bool ip_06_setupDone;
                SampleIndex ip_07_lastIndex;
                number ip_07_lastValue;
                SampleIndex ip_07_resetCount;
                signal ip_07_sigbuf;
                bool ip_07_setupDone;
                number param_12_lastValue;
                number param_13_lastValue;
                number param_14_lastValue;
                SampleIndex ip_08_lastIndex;
                number ip_08_lastValue;
                SampleIndex ip_08_resetCount;
                signal ip_08_sigbuf;
                bool ip_08_setupDone;
                number param_15_lastValue;
                number param_16_lastValue;
                int ctlin_01_status;
                int ctlin_01_byte1;
                int ctlin_01_inchan;
                int ctlin_02_status;
                int ctlin_02_byte1;
                int ctlin_02_inchan;
                int ctlin_03_status;
                int ctlin_03_byte1;
                int ctlin_03_inchan;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
                RNBOSubpatcher_61* p_05;
                RNBOSubpatcher_62* p_06;
                RNBOSubpatcher_63* p_07;
            
    };
    
    RNBOSubpatcher_67()
    {
    }
    
    ~RNBOSubpatcher_67()
    {
        delete this->p_08;
        delete this->p_09;
        delete this->p_10;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    number samplerate() const {
        return this->sr;
    }
    
    Index getNumMidiInputPorts() const {
        return 1;
    }
    
    void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
        this->updateTime(time);
        this->p_10_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
        this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    }
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->ip_09_perform(this->signals[0], n);
        this->p_10_perform(this->signals[0], this->signals[1], n);
        this->p_09_perform(this->signals[1], this->signals[0], n);
        this->dcblock_tilde_01_perform(this->signals[0], this->dcblock_tilde_01_gain, this->signals[1], n);
        this->ip_10_perform(this->signals[0], n);
        this->dspexpr_12_perform(this->signals[0], this->dspexpr_12_in2, this->signals[2], n);
        this->p_08_perform(this->signals[1], this->signals[2], this->signals[3], this->signals[4], n);
        this->scopetilde_01_perform(this->signals[4], this->zeroBuffer, n);
        this->latch_tilde_01_perform(this->signals[0], this->signals[2], this->signals[4], n);
        this->dspexpr_11_perform(this->signals[4], this->dspexpr_11_in2, this->signals[2], n);
        this->dspexpr_10_perform(this->signals[3], this->signals[2], this->signals[4], n);
        this->signaladder_01_perform(this->signals[4], out2, out2, n);
        this->signaladder_02_perform(this->signals[4], out1, out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 5; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->ip_09_sigbuf = resizeSignal(this->ip_09_sigbuf, this->maxvs, maxBlockSize);
            this->ip_10_sigbuf = resizeSignal(this->ip_10_sigbuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->ip_09_dspsetup(forceDSPSetup);
        this->dcblock_tilde_01_dspsetup(forceDSPSetup);
        this->ip_10_dspsetup(forceDSPSetup);
        this->scopetilde_01_dspsetup(forceDSPSetup);
        this->latch_tilde_01_dspsetup(forceDSPSetup);
        this->p_08->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_09->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_10->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
        this->p_08->setVoiceIndex(index);
        this->p_09->setVoiceIndex(index);
        this->p_10->setVoiceIndex(index);
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
        this->p_08->setNoteNumber(noteNumber);
        this->p_09->setNoteNumber(noteNumber);
        this->p_10->setNoteNumber(noteNumber);
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_08 = new RNBOSubpatcher_64();
        this->p_08->setEngineAndPatcher(this->getEngine(), this);
        this->p_08->initialize();
        this->p_08->setParameterOffset(this->getParameterOffset(this->p_08));
        this->p_09 = new RNBOSubpatcher_65();
        this->p_09->setEngineAndPatcher(this->getEngine(), this);
        this->p_09->initialize();
        this->p_09->setParameterOffset(this->getParameterOffset(this->p_09));
        this->p_10 = new RNBOSubpatcher_66();
        this->p_10->setEngineAndPatcher(this->getEngine(), this);
        this->p_10->initialize();
        this->p_10->setParameterOffset(this->getParameterOffset(this->p_10));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_08->getPreset(getSubState(getSubState(preset, "__sps"), "env.adsr"));
        this->p_09->getPreset(getSubState(getSubState(preset, "__sps"), "filters"));
        this->p_10->getPreset(getSubState(getSubState(preset, "__sps"), "oscillators"));
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        RNBO_UNUSED(v);
        this->updateTime(time);
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_08->getNumParameters())
                this->p_08->setParameterValue(index, v, time);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                this->p_09->setParameterValue(index, v, time);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                this->p_10->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->getParameterValue(index);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->getParameterValue(index);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterValue getPolyParameterValue(PatcherInterface** voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        PatcherInterface** voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 8; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0 + this->p_08->getNumParameters() + this->p_09->getNumParameters() + this->p_10->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->getParameterName(index);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->getParameterName(index);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->getParameterId(index);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->getParameterId(index);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            default:
                {
                index -= 0;
    
                if (index < this->p_08->getNumParameters())
                    this->p_08->getParameterInfo(index, info);
    
                index -= this->p_08->getNumParameters();
    
                if (index < this->p_09->getNumParameters())
                    this->p_09->getParameterInfo(index, info);
    
                index -= this->p_09->getNumParameters();
    
                if (index < this->p_10->getNumParameters())
                    this->p_10->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_08)
            return 0;
    
        if (subpatcher == this->p_09)
            return 0 + this->p_08->getNumParameters();
    
        if (subpatcher == this->p_10)
            return 0 + this->p_08->getNumParameters() + this->p_09->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            index -= 0;
    
            if (index < this->p_08->getNumParameters())
                return this->p_08->constrainParameterValue(index, value);
    
            index -= this->p_08->getNumParameters();
    
            if (index < this->p_09->getNumParameters())
                return this->p_09->constrainParameterValue(index, value);
    
            index -= this->p_09->getNumParameters();
    
            if (index < this->p_10->getNumParameters())
                return this->p_10->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_08->processNumMessage(tag, objectId, time, payload);
        this->p_09->processNumMessage(tag, objectId, time, payload);
        this->p_10->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_08->processListMessage(tag, objectId, time, payload);
        this->p_09->processListMessage(tag, objectId, time, payload);
        this->p_10->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_08->processBangMessage(tag, objectId, time);
        this->p_09->processBangMessage(tag, objectId, time);
        this->p_10->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("poly/scope~_obj-16"):
            {
            return "poly/scope~_obj-16";
            }
        case TAG("monitor"):
            {
            return "monitor";
            }
        }
    
        auto subpatchResult_0 = this->p_08->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_09->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_10->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->p_08->processDataViewUpdate(index, time);
        this->p_09->processDataViewUpdate(index, time);
        this->p_10->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->ip_09_init();
        this->ip_10_init();
        this->p_08->initializeObjects();
        this->p_09->initializeObjects();
        this->p_10->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_08->startup();
        this->p_09->startup();
        this->p_10->startup();
    }
    
    void allocateDataRefs() {
        this->p_08->allocateDataRefs();
        this->p_09->allocateDataRefs();
        this->p_10->allocateDataRefs();
    }
    
    void p_10_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(port);
        RNBO_UNUSED(channel);
        RNBO_UNUSED(status);
        this->p_10->processMidiEvent(_currentTime, 0, data, length);
    }
    
    void notein_01_outchannel_set(number ) {}
    
    void notein_01_releasevelocity_set(number ) {}
    
    void ip_10_value_set(number v) {
        this->ip_10_value = v;
        this->ip_10_fillSigBuf();
        this->ip_10_lastValue = v;
    }
    
    void notein_01_velocity_set(number v) {
        this->ip_10_value_set(v);
    }
    
    void ip_09_value_set(number v) {
        this->ip_09_value = v;
        this->ip_09_fillSigBuf();
        this->ip_09_lastValue = v;
    }
    
    void notein_01_notenumber_set(number v) {
        this->ip_09_value_set(v);
    }
    
    void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (channel == this->notein_01_channel || this->notein_01_channel == 0) {
            if (status == 144 || status == 128) {
                this->notein_01_outchannel_set(channel);
    
                if (status == 128) {
                    this->notein_01_releasevelocity_set(data[2]);
                    this->notein_01_velocity_set(0);
                } else {
                    this->notein_01_releasevelocity_set(0);
                    this->notein_01_velocity_set(data[2]);
                }
    
                this->notein_01_notenumber_set(data[1]);
            }
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void ip_09_perform(SampleValue * out, Index n) {
        auto __ip_09_lastValue = this->ip_09_lastValue;
        auto __ip_09_lastIndex = this->ip_09_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_09_lastIndex ? __ip_09_lastValue : this->ip_09_sigbuf[(Index)i]);
        }
    
        __ip_09_lastIndex = 0;
        this->ip_09_lastIndex = __ip_09_lastIndex;
    }
    
    void p_10_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        // subpatcher: oscillators
        ConstSampleArray<1> ins = {in1};
    
        SampleArray<1> outs = {out1};
        this->p_10->process(ins, 1, outs, 1, n);
    }
    
    void p_09_perform(const SampleValue * in1, SampleValue * out1, Index n) {
        // subpatcher: filters
        ConstSampleArray<1> ins = {in1};
    
        SampleArray<1> outs = {out1};
        this->p_09->process(ins, 1, outs, 1, n);
    }
    
    void dcblock_tilde_01_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
        RNBO_UNUSED(gain);
        auto __dcblock_tilde_01_ym1 = this->dcblock_tilde_01_ym1;
        auto __dcblock_tilde_01_xm1 = this->dcblock_tilde_01_xm1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number y = x[(Index)i] - __dcblock_tilde_01_xm1 + __dcblock_tilde_01_ym1 * 0.9997;
            __dcblock_tilde_01_xm1 = x[(Index)i];
            __dcblock_tilde_01_ym1 = y;
            out1[(Index)i] = y;
        }
    
        this->dcblock_tilde_01_xm1 = __dcblock_tilde_01_xm1;
        this->dcblock_tilde_01_ym1 = __dcblock_tilde_01_ym1;
    }
    
    void ip_10_perform(SampleValue * out, Index n) {
        auto __ip_10_lastValue = this->ip_10_lastValue;
        auto __ip_10_lastIndex = this->ip_10_lastIndex;
    
        for (Index i = 0; i < n; i++) {
            out[(Index)i] = ((SampleIndex)(i) >= __ip_10_lastIndex ? __ip_10_lastValue : this->ip_10_sigbuf[(Index)i]);
        }
    
        __ip_10_lastIndex = 0;
        this->ip_10_lastIndex = __ip_10_lastIndex;
    }
    
    void dspexpr_12_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] > 0;//#map:_###_obj_###_:1
        }
    }
    
    void p_08_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        // subpatcher: env.adsr
        ConstSampleArray<2> ins = {in1, in2};
    
        SampleArray<2> outs = {out1, out2};
        this->p_08->process(ins, 2, outs, 2, n);
    }
    
    void scopetilde_01_perform(const SampleValue * x, const SampleValue * y, Index n) {
        auto __scopetilde_01_ysign = this->scopetilde_01_ysign;
        auto __scopetilde_01_ymonitorvalue = this->scopetilde_01_ymonitorvalue;
        auto __scopetilde_01_xsign = this->scopetilde_01_xsign;
        auto __scopetilde_01_xmonitorvalue = this->scopetilde_01_xmonitorvalue;
        auto __scopetilde_01_mode = this->scopetilde_01_mode;
    
        for (Index i = 0; i < n; i++) {
            number xval = x[(Index)i];
            number yval = y[(Index)i];
    
            if (__scopetilde_01_mode == 1) {
                number xabsval = rnbo_abs(xval);
    
                if (xabsval > __scopetilde_01_xmonitorvalue) {
                    __scopetilde_01_xmonitorvalue = xabsval;
                    __scopetilde_01_xsign = (xval < 0 ? -1 : 1);
                }
    
                number yabsval = rnbo_abs(yval);
    
                if (yabsval > __scopetilde_01_ymonitorvalue) {
                    __scopetilde_01_ymonitorvalue = yabsval;
                    __scopetilde_01_ysign = (yval < 0 ? -1 : 1);
                }
            } else {
                __scopetilde_01_xmonitorvalue = xval;
                __scopetilde_01_xsign = 1;
                __scopetilde_01_ymonitorvalue = yval;
                __scopetilde_01_ysign = 1;
            }
    
            this->scopetilde_01_effectiveCount--;
    
            if (this->scopetilde_01_effectiveCount <= 0) {
                this->scopetilde_01_updateEffectiveCount();
                this->scopetilde_01_monitorbuffer->push(__scopetilde_01_xmonitorvalue * __scopetilde_01_xsign);
    
                if (__scopetilde_01_mode == 1)
                    __scopetilde_01_xmonitorvalue = 0;
    
                if (this->scopetilde_01_monitorbuffer->length >= 128 * (1 + 0)) {
                    this->getEngine()->sendListMessage(
                        TAG("monitor"),
                        TAG("poly/scope~_obj-16"),
                        this->scopetilde_01_monitorbuffer,
                        this->_currentTime
                    );;
    
                    this->scopetilde_01_monitorbuffer->length = 0;
                }
            }
        }
    
        this->scopetilde_01_xmonitorvalue = __scopetilde_01_xmonitorvalue;
        this->scopetilde_01_xsign = __scopetilde_01_xsign;
        this->scopetilde_01_ymonitorvalue = __scopetilde_01_ymonitorvalue;
        this->scopetilde_01_ysign = __scopetilde_01_ysign;
    }
    
    void latch_tilde_01_perform(const Sample * x, const Sample * control, SampleValue * out1, Index n) {
        auto __latch_tilde_01_value = this->latch_tilde_01_value;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (control[(Index)i] != 0.)
                __latch_tilde_01_value = x[(Index)i];
    
            out1[(Index)i] = __latch_tilde_01_value;
        }
    
        this->latch_tilde_01_value = __latch_tilde_01_value;
    }
    
    void dspexpr_11_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] / (number)127;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_10_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void signaladder_01_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void dcblock_tilde_01_reset() {
        this->dcblock_tilde_01_xm1 = 0;
        this->dcblock_tilde_01_ym1 = 0;
    }
    
    void dcblock_tilde_01_dspsetup(bool force) {
        if ((bool)(this->dcblock_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->dcblock_tilde_01_reset();
        this->dcblock_tilde_01_setupDone = true;
    }
    
    void ip_09_init() {
        this->ip_09_lastValue = this->ip_09_value;
    }
    
    void ip_09_fillSigBuf() {
        if ((bool)(this->ip_09_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_09_lastIndex); i < k; i++) {
                if (this->ip_09_resetCount > 0) {
                    this->ip_09_sigbuf[(Index)i] = 1;
                    this->ip_09_resetCount--;
                } else {
                    this->ip_09_sigbuf[(Index)i] = this->ip_09_lastValue;
                }
            }
    
            this->ip_09_lastIndex = k;
        }
    }
    
    void ip_09_dspsetup(bool force) {
        if ((bool)(this->ip_09_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_09_lastIndex = 0;
        this->ip_09_setupDone = true;
    }
    
    void ip_10_init() {
        this->ip_10_lastValue = this->ip_10_value;
    }
    
    void ip_10_fillSigBuf() {
        if ((bool)(this->ip_10_sigbuf)) {
            SampleIndex k = (SampleIndex)(this->sampleOffsetIntoNextAudioBuffer);
    
            if (k >= (SampleIndex)(this->vs))
                k = (SampleIndex)(this->vs) - 1;
    
            for (SampleIndex i = (SampleIndex)(this->ip_10_lastIndex); i < k; i++) {
                if (this->ip_10_resetCount > 0) {
                    this->ip_10_sigbuf[(Index)i] = 1;
                    this->ip_10_resetCount--;
                } else {
                    this->ip_10_sigbuf[(Index)i] = this->ip_10_lastValue;
                }
            }
    
            this->ip_10_lastIndex = k;
        }
    }
    
    void ip_10_dspsetup(bool force) {
        if ((bool)(this->ip_10_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->ip_10_lastIndex = 0;
        this->ip_10_setupDone = true;
    }
    
    void latch_tilde_01_reset() {
        this->latch_tilde_01_value = 0;
    }
    
    void latch_tilde_01_dspsetup(bool force) {
        if ((bool)(this->latch_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->latch_tilde_01_reset();
        this->latch_tilde_01_setupDone = true;
    }
    
    void scopetilde_01_updateEffectiveCount() {
        number effectiveCount = 256 * 1 + 256 * 0;
        this->scopetilde_01_effectiveCount = this->maximum(effectiveCount, 256);
    }
    
    void scopetilde_01_dspsetup(bool force) {
        if ((bool)(this->scopetilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        {
            this->scopetilde_01_mode = 1;
        }
    
        this->getEngine()->sendListMessage(
            TAG("setup"),
            TAG("poly/scope~_obj-16"),
            {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_01_mode},
            this->_currentTime
        );;
    
        this->scopetilde_01_updateEffectiveCount();
        this->scopetilde_01_setupDone = true;
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        p_08_target = 0;
        dspexpr_10_in1 = 0;
        dspexpr_10_in2 = 1;
        dcblock_tilde_01_x = 0;
        dcblock_tilde_01_gain = 0.9997;
        p_09_target = 0;
        p_10_target = 0;
        ip_09_value = 0;
        ip_09_impulse = 0;
        notein_01_channel = 0;
        dspexpr_11_in1 = 0;
        dspexpr_11_in2 = 127;
        ip_10_value = 0;
        ip_10_impulse = 0;
        latch_tilde_01_x = 0;
        latch_tilde_01_control = 0;
        dspexpr_12_in1 = 0;
        dspexpr_12_in2 = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        dcblock_tilde_01_xm1 = 0;
        dcblock_tilde_01_ym1 = 0;
        dcblock_tilde_01_setupDone = false;
        ip_09_lastIndex = 0;
        ip_09_lastValue = 0;
        ip_09_resetCount = 0;
        ip_09_sigbuf = nullptr;
        ip_09_setupDone = false;
        notein_01_status = 0;
        notein_01_byte1 = -1;
        notein_01_inchan = 0;
        ip_10_lastIndex = 0;
        ip_10_lastValue = 0;
        ip_10_resetCount = 0;
        ip_10_sigbuf = nullptr;
        ip_10_setupDone = false;
        latch_tilde_01_value = 0;
        latch_tilde_01_setupDone = false;
        scopetilde_01_lastValue = 0;
        scopetilde_01_effectiveCount = 256;
        scopetilde_01_xsign = 1;
        scopetilde_01_ysign = 1;
        scopetilde_01_mode = 0;
        scopetilde_01_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number p_08_target;
        number dspexpr_10_in1;
        number dspexpr_10_in2;
        number dcblock_tilde_01_x;
        number dcblock_tilde_01_gain;
        number p_09_target;
        number p_10_target;
        number ip_09_value;
        number ip_09_impulse;
        number notein_01_channel;
        number dspexpr_11_in1;
        number dspexpr_11_in2;
        number ip_10_value;
        number ip_10_impulse;
        number latch_tilde_01_x;
        number latch_tilde_01_control;
        number dspexpr_12_in1;
        number dspexpr_12_in2;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[5];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number dcblock_tilde_01_xm1;
        number dcblock_tilde_01_ym1;
        bool dcblock_tilde_01_setupDone;
        SampleIndex ip_09_lastIndex;
        number ip_09_lastValue;
        SampleIndex ip_09_resetCount;
        signal ip_09_sigbuf;
        bool ip_09_setupDone;
        int notein_01_status;
        int notein_01_byte1;
        int notein_01_inchan;
        SampleIndex ip_10_lastIndex;
        number ip_10_lastValue;
        SampleIndex ip_10_resetCount;
        signal ip_10_sigbuf;
        bool ip_10_setupDone;
        number latch_tilde_01_value;
        bool latch_tilde_01_setupDone;
        number scopetilde_01_lastValue;
        number scopetilde_01_effectiveCount;
        number scopetilde_01_xmonitorvalue;
        number scopetilde_01_ymonitorvalue;
        list scopetilde_01_monitorbuffer;
        number scopetilde_01_xsign;
        number scopetilde_01_ysign;
        Int scopetilde_01_mode;
        bool scopetilde_01_setupDone;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_64* p_08;
        RNBOSubpatcher_65* p_09;
        RNBOSubpatcher_66* p_10;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    for (int i = 0; i < 8; i++) {
        delete poly[i];
    }
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->midiin_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 1;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    this->poly_perform(out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->globaltransport_dspsetup(forceDSPSetup);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->RNBODefaultMtofLookupTable256);
        break;
        }
    case 1:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void fillRNBODefaultMtofLookupTable256(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        number midivalue = -256. + (number)512. / (bufsize - 1) * i;
        buffer[i] = rnbo_exp(.057762265 * (midivalue - 69.0));
    }
}

void fillRNBODefaultSinus(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultMtofLookupTable256(ref);
        break;
        }
    case 1:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processDataViewUpdate(index, time);
    }
}

void initialize() {
    this->RNBODefaultMtofLookupTable256 = initDataRef("RNBODefaultMtofLookupTable256", true, nullptr, "buffer~");
    this->RNBODefaultSinus = initDataRef("RNBODefaultSinus", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultMtofLookupTable256->setIndex(0);
    this->RNBODefaultSinus->setIndex(1);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    for (Index i = 0; i < 8; i++) {
        this->poly[(Index)i] = new RNBOSubpatcher_67();
        this->poly[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->poly[(Index)i]->initialize();
        this->poly[(Index)i]->setParameterOffset(this->getParameterOffset(this->poly[0]));
        this->poly[(Index)i]->setVoiceIndex(i + 1);
    }
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";

    for (Index i = 0; i < 8; i++)
        this->poly[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "poly", i));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_08->param_01_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "env.adsr"), "attack")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_08->param_02_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "env.adsr"), "decay")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_08->param_03_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "env.adsr"), "sustain")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_08->param_04_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "env.adsr"), "release")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_09->param_05_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "filters"), "filtertype")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_09->param_06_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "filters"), "cutoff")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_09->param_07_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "filters"), "resonance_mod")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_10->param_11_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "oscillators"), "levelB")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_10->param_12_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "oscillators"), "levelA")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_10->param_13_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "oscillators"), "detuneB")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_10->param_14_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "oscillators"), "detuneA")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_10->param_15_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "oscillators"), "detuneC")
    );

    for (Index i1 = 0; i1 < 8; i1++) this->poly[i1]->p_10->param_16_setPresetValue(
        getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i1), "__sps"), "oscillators"), "levelC")
    );

    for (Index i2 = 0; i2 < 8; i2++) this->poly[i2]->p_10->p_05->param_08_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i2), "__sps"), "oscillators"), "__sps"), "oscB"), "mode")
    );

    for (Index i2 = 0; i2 < 8; i2++) this->poly[i2]->p_10->p_06->param_09_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i2), "__sps"), "oscillators"), "__sps"), "oscA"), "mode")
    );

    for (Index i2 = 0; i2 < 8; i2++) this->poly[i2]->p_10->p_07->param_10_setPresetValue(
        getSubState(getSubState(getSubState(getSubState(getSubState(getSubStateAt(getSubState(preset, "__sps"), "poly", i2), "__sps"), "oscillators"), "__sps"), "oscC"), "mode")
    );
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    RNBO_UNUSED(v);
    this->updateTime(time);

    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->poly[0]->getNumParameters())
            this->poly[0]->setPolyParameterValue((PatcherInterface**)this->poly, index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->poly[0]->getNumParameters())
            return this->poly[0]->getPolyParameterValue((PatcherInterface**)this->poly, index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 0 + this->poly[0]->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterName(index);
            }
        }

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterId(index);
            }
        }

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        default:
            {
            index -= 0;

            if (index < this->poly[0]->getNumParameters()) {
                for (Index i = 0; i < 8; i++) {
                    this->poly[i]->getParameterInfo(index, info);
                }
            }

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->poly[0])
        return 0;

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    default:
        {
        index -= 0;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->constrainParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processNumMessage(tag, objectId, time, payload);
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processListMessage(tag, objectId, time, payload);
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->processBangMessage(tag, objectId, time);
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->poly[0]->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    for (Index i = 0; i < 8; i++) {
        this->poly[i]->allocateDataRefs();
    }

    if (this->RNBODefaultMtofLookupTable256->hasRequestedSize()) {
        if (this->RNBODefaultMtofLookupTable256->wantsFill())
            this->fillRNBODefaultMtofLookupTable256(this->RNBODefaultMtofLookupTable256);

        this->getEngine()->sendDataRefUpdated(0);
    }

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->midinotecontroller_01_init();

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->initializeObjects();
    }
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    for (Index i = 0; i < 8; i++) {
        this->poly[i]->startup();
    }

    this->processParamInitEvents();
}

void midinotecontroller_01_currenttarget_set(number v) {
    this->midinotecontroller_01_currenttarget = v;
}

void poly_target_set(number v) {
    this->poly_target = v;
    this->midinotecontroller_01_currenttarget_set(v);
}

void midinotecontroller_01_target_set(number v) {
    this->poly_target_set(v);
}

void poly_midiininternal_set(number v) {
    Index sendlen = 0;
    this->poly_currentStatus = parseMidi(this->poly_currentStatus, (int)(v), this->poly_mididata[0]);

    switch ((int)this->poly_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        this->poly_mididata[0] = (uint8_t)(v);
        this->poly_mididata[1] = 0;
        break;
        }
    case MIDI_SecondByteReceived:
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
        {
        this->poly_mididata[1] = (uint8_t)(v);

        if (this->poly_currentStatus == MIDI_ProgramChange || this->poly_currentStatus == MIDI_ChannelPressure) {
            sendlen = 2;
        }

        break;
        }
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    default:
        {
        this->poly_mididata[2] = (uint8_t)(v);
        sendlen = 3;
        break;
        }
    }

    if (sendlen > 0) {
        number i;

        if (this->poly_target > 0 && this->poly_target <= 8) {
            i = this->poly_target - 1;
            this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
        } else if (this->poly_target == 0) {
            for (i = 0; i < 8; i++) {
                this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
            }
        }
    }
}

void midinotecontroller_01_midiout_set(number v) {
    this->poly_midiininternal_set(v);
}

void poly_noteNumber_set(number v) {
    if (this->poly_target > 0) {
        this->poly[(Index)(this->poly_target - 1)]->setNoteNumber((int)(v));
    }
}

void midinotecontroller_01_noteNumber_set(number v) {
    this->poly_noteNumber_set(v);
}

void midinotecontroller_01_voicestatus_set(const list& v) {
    if (v[1] == 1) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v[0]);
        this->midinotecontroller_01_noteNumber_set(0);
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void poly_voicestatus_set(const list& v) {
    this->midinotecontroller_01_voicestatus_set(v);
}

void poly_activevoices_set(number ) {}

void poly_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 8; i++) {
            this->poly[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 8) {
            this->poly[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->poly_voicestatus_set(tmp);
    this->poly_activevoices_set(this->poly_calcActiveVoices());
}

void midinotecontroller_01_mute_set(const list& v) {
    this->poly_mute_set(v);
}

void midinotecontroller_01_midiin_set(number v) {
    this->midinotecontroller_01_midiin = v;
    int val = (int)(v);

    this->midinotecontroller_01_currentStatus = parseMidi(
        this->midinotecontroller_01_currentStatus,
        (int)(v),
        this->midinotecontroller_01_status
    );

    switch ((int)this->midinotecontroller_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        {
            this->midinotecontroller_01_status = val;
            this->midinotecontroller_01_byte1 = -1;
            break;
        }
        }
    case MIDI_SecondByteReceived:
        {
        this->midinotecontroller_01_byte1 = val;
        break;
        }
    case MIDI_NoteOn:
        {
        {
            bool sendnoteoff = true;
            number target = 1;
            MillisecondTime oldest = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[0]);
            number target_state = this->midinotecontroller_01_voice_state[0];

            for (Index i = 0; i < 8; i++) {
                number candidate_state = this->midinotecontroller_01_voice_state[(Index)i];

                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == this->midinotecontroller_01_byte1 && candidate_state == MIDI_NoteState_On) {
                    sendnoteoff = false;
                    target = i + 1;
                    break;
                }

                if (i > 0) {
                    if (candidate_state != MIDI_NoteState_On || target_state == MIDI_NoteState_On) {
                        MillisecondTime candidate_ontime = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[(Index)i]);

                        if (candidate_ontime < oldest || (target_state == MIDI_NoteState_On && candidate_state != MIDI_NoteState_On)) {
                            target = i + 1;
                            oldest = candidate_ontime;
                            target_state = candidate_state;
                        }
                    }
                }
            }

            if ((bool)(sendnoteoff))
                this->midinotecontroller_01_sendnoteoff((int)(target));

            int i = (int)(target - 1);
            this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_On;
            this->midinotecontroller_01_voice_lastontime[(Index)i] = this->currenttime();
            this->midinotecontroller_01_voice_notenumber[(Index)i] = this->midinotecontroller_01_byte1;
            this->midinotecontroller_01_voice_channel[(Index)i] = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index j = 0; j < 128; j++) {
                if (this->midinotecontroller_01_notesdown[(Index)j] == 0) {
                    this->midinotecontroller_01_notesdown[(Index)j] = this->midinotecontroller_01_voice_notenumber[(Index)i];
                    break;
                }
            }

            this->midinotecontroller_01_note_lastvelocity[(Index)this->midinotecontroller_01_voice_notenumber[(Index)i]] = val;
            this->midinotecontroller_01_sendpitchbend((int)(i));
            this->midinotecontroller_01_sendpressure((int)(i));
            this->midinotecontroller_01_sendtimbre((int)(i));
            this->midinotecontroller_01_muteval[0] = target;
            this->midinotecontroller_01_muteval[1] = 0;
            this->midinotecontroller_01_mute_set(this->midinotecontroller_01_muteval);
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(target);
            this->midinotecontroller_01_noteNumber_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);

            this->midinotecontroller_01_midiout_set(
                (BinOpInt)((BinOpInt)MIDI_NoteOnMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
            );

            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
            this->midinotecontroller_01_midiout_set(val);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_NoteOff:
        {
        {
            number target = 0;
            number notenumber = this->midinotecontroller_01_byte1;
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == notenumber && this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_On) {
                    target = i + 1;
                    break;
                }
            }

            if (target > 0) {
                int i = (int)(target - 1);
                Index j = (Index)(channel);
                bool ignoresustainchannel = true;

                if ((bool)(this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)])) {
                    this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Sustained;
                } else {
                    number currentTarget = this->midinotecontroller_01_currenttarget;
                    this->midinotecontroller_01_target_set(target);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                    this->midinotecontroller_01_midiout_set(v);
                    this->midinotecontroller_01_target_set(currentTarget);

                    if (this->midinotecontroller_01_currentStatus == MIDI_NoteOff) {
                        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                    }
                }
            } else
                {}

            bool found = false;

            for (Index i = 0; i < 128; i++) {
                if (this->midinotecontroller_01_notesdown[(Index)i] == 0) {
                    break;
                } else if (this->midinotecontroller_01_notesdown[(Index)i] == notenumber) {
                    found = true;
                }

                if ((bool)(found)) {
                    this->midinotecontroller_01_notesdown[(Index)i] = this->midinotecontroller_01_notesdown[(Index)(i + 1)];
                }
            }

            break;
        }
        }
    case MIDI_Aftertouch:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_midiout_set(v);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_CC:
        {
        {
            bool sendToAllVoices = true;

            switch ((int)this->midinotecontroller_01_byte1) {
            case MIDI_CC_Sustain:
                {
                {
                    bool pedaldown = (bool)((val >= 64 ? true : false));
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Index j = (Index)(channel);
                    bool ignoresustainchannel = true;
                    this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)] = pedaldown;

                    if ((bool)(!(bool)(pedaldown))) {
                        for (Index i = 0; i < 8; i++) {
                            if (((bool)(ignoresustainchannel) || this->midinotecontroller_01_voice_channel[(Index)i] == channel) && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_Sustained) {
                                number currentTarget = this->midinotecontroller_01_currenttarget;
                                this->midinotecontroller_01_target_set(i + 1);
                                this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)j));
                                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
                                this->midinotecontroller_01_midiout_set(64);
                                this->midinotecontroller_01_target_set(currentTarget);
                                this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                            }
                        }
                    }

                    break;
                }
                }
            case MIDI_CC_TimbreMSB:
                {
                {
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    int k = (int)(v);
                    number timbre = (BinOpInt)(((BinOpInt)((BinOpInt)k & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32));
                    this->midinotecontroller_01_channel_timbre[(Index)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F)] = timbre;

                    for (Index i = 0; i < 8; i++) {
                        if (this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
                            this->midinotecontroller_01_sendtimbre(i);
                        }
                    }

                    sendToAllVoices = false;
                    break;
                }
                }
            case MIDI_CC_TimbreLSB:
                {
                {
                    break;
                }
                }
            case MIDI_CC_AllNotesOff:
                {
                {
                    this->midinotecontroller_01_sendallnotesoff();
                    break;
                }
                }
            }

            if ((bool)(sendToAllVoices)) {
                number currentTarget = this->midinotecontroller_01_currenttarget;
                this->midinotecontroller_01_target_set(0);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                this->midinotecontroller_01_midiout_set(v);
                this->midinotecontroller_01_target_set(currentTarget);
            }

            break;
        }
        }
    case MIDI_ProgramChange:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_ChannelPressure:
        {
        {
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (number i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    int k = (int)(channel);
                    this->midinotecontroller_01_channel_pressure[(Index)k] = v;
                    this->midinotecontroller_01_sendpressure(i);
                }
            }

            break;
        }
        }
    case MIDI_PitchBend:
        {
        {
            number bendamount = (BinOpInt)((BinOpInt)this->midinotecontroller_01_byte1 | (BinOpInt)((BinOpInt)val << imod_nocast((UBinOpInt)7, 32)));
            int channel = (int)((BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F));
            this->midinotecontroller_01_channel_pitchbend[(Index)channel] = bendamount;

            for (Index i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    this->midinotecontroller_01_sendpitchbend(i);
                }
            }

            break;
        }
        }
    }
}

void poly_midiin_set(number v) {
    this->poly_midiin = v;
    this->midinotecontroller_01_midiin_set(v);
}

void midiin_midiout_set(number v) {
    this->poly_midiin_set(v);
}

void midiin_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_midiout_set(data[i]);
    }
}

void poly_perform(SampleValue * out1, SampleValue * out2, Index n) {
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 8; i++)
        this->poly[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

number poly_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 8; i++) {
            if ((bool)(!(bool)(this->poly[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void midinotecontroller_01_init() {
    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_channel_pitchbend[(Index)i] = 0x2000;
    }

    for (Index i = 0; i < 8; i++) {
        this->midinotecontroller_01_voice_lastontime[(Index)i] = -1;
    }
}

void midinotecontroller_01_sendnoteoff(int target) {
    int i = (int)(target - 1);

    if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(target);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
        );

        this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
        this->midinotecontroller_01_midiout_set(64);
        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpitchbend(int v) {
    if (v >= 0 && v < 8) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v + 1);
        int totalbendamount = (int)(this->midinotecontroller_01_channel_pitchbend[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_PitchBendMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
        );

        this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)totalbendamount & (BinOpInt)0x7F));

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)((BinOpInt)totalbendamount >> imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)7, 32), 32)) & (BinOpInt)0x7F)
        );

        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpressure(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_ChannelPressureMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(
        this->midinotecontroller_01_channel_pressure[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendtimbre(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreLSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreMSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] >> imod_nocast((UBinOpInt)7, 32)) & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendallnotesoff() {
    for (Index i = 1; i <= 8; i++) {
        this->midinotecontroller_01_sendnoteoff(i);
    }
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    midiin_port = 0;
    midiout_port = 0;
    poly_target = 0;
    poly_midiin = 0;
    midinotecontroller_01_currenttarget = 0;
    midinotecontroller_01_midiin = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    midiout_currentStatus = -1;
    midiout_status = -1;
    midiout_byte1 = -1;
    poly_currentStatus = -1;
    poly_mididata[0] = 0;
    poly_mididata[1] = 0;
    poly_mididata[2] = 0;
    midinotecontroller_01_currentStatus = -1;
    midinotecontroller_01_status = -1;
    midinotecontroller_01_byte1 = -1;
    midinotecontroller_01_zone_masterchannel = 1;
    midinotecontroller_01_zone_numnotechannels = 15;
    midinotecontroller_01_zone_masterpitchbendrange = 2;
    midinotecontroller_01_zone_pernotepitchbendrange = 48;
    midinotecontroller_01_muteval = { 0, 0 };
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number midiin_port;
    number midiout_port;
    number poly_target;
    number poly_midiin;
    number midinotecontroller_01_currenttarget;
    number midinotecontroller_01_midiin;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    int midiout_currentStatus;
    int midiout_status;
    int midiout_byte1;
    list midiout_sysex;
    int poly_currentStatus;
    uint8_t poly_mididata[3];
    int midinotecontroller_01_currentStatus;
    int midinotecontroller_01_status;
    int midinotecontroller_01_byte1;
    int midinotecontroller_01_zone_masterchannel;
    int midinotecontroller_01_zone_numnotechannels;
    int midinotecontroller_01_zone_masterpitchbendrange;
    int midinotecontroller_01_zone_pernotepitchbendrange;
    number midinotecontroller_01_channel_pitchbend[16] = { };
    number midinotecontroller_01_channel_pressure[16] = { };
    number midinotecontroller_01_channel_timbre[16] = { };
    Int midinotecontroller_01_channel_sustain[16] = { };
    MillisecondTime midinotecontroller_01_voice_lastontime[8] = { };
    number midinotecontroller_01_voice_notenumber[8] = { };
    number midinotecontroller_01_voice_channel[8] = { };
    number midinotecontroller_01_voice_state[8] = { };
    number midinotecontroller_01_notesdown[129] = { };
    number midinotecontroller_01_note_lastvelocity[128] = { };
    list midinotecontroller_01_muteval;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef RNBODefaultMtofLookupTable256;
    DataRef RNBODefaultSinus;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_67* poly[8];

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

