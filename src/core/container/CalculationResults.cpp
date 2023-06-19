//
// Created by zhao on 2023/6/18.
//

#include "CalculationResults.h"

#include <utility>

namespace ME {

    int CalculationBooleanResults::getResultLayers() {
        return this->Layers;
    }

    string CalculationBooleanResults::getCalculationSourceName() {
        return this->source;
    }

    double CalculationBooleanResults::getResult_double() const {
        return this->getResult() ? 1 : 0;
    }

    bool CalculationBooleanResults::getResult() const {
        return this->result;
    }

    CalculationBooleanResults::CalculationBooleanResults(const bool result, string source, const int layers,
                                                         const double left, const double right) : result(result),
                                                                                                  source(std::move(
                                                                                                          source)),
                                                                                                  Layers(layers),
                                                                                                  left(left),
                                                                                                  right(right) {}

    double CalculationBooleanResults::getLeft() const {
        return this->left;
    }

    double CalculationBooleanResults::getRight() const {
        return this->right;
    }

    bool CalculationBooleanResults::operator==(const CalculationBooleanResults &other) const {
        return this->result == other.result;
    }

    bool CalculationBooleanResults::operator!=(const CalculationBooleanResults &other) const {
        return this->result != other.result;
    }

    size_t CalculationBooleanResults::operator()(const CalculationBooleanResults &person) const {
        return std::hash<std::string>{}(person.source) ^ std::hash<bool>{}(person.result) ^
               std::hash<double>{}(person.left) ^ std::hash<double>{}(person.right);
    }

    CalculationBooleanResults::~CalculationBooleanResults() = default;

    // ******************************************************


    int CalculationNumberResults::getResultLayers() {
        return this->result_layers;
    }

    string CalculationNumberResults::getCalculationSourceName() {
        return this->source;
    }

    double CalculationNumberResults::getResult_double() const {
        return this->result;
    }

    bool CalculationNumberResults::operator<(const CalculationNumberResults &rhs) const {
        return result < rhs.result;
    }

    bool CalculationNumberResults::operator>(const CalculationNumberResults &rhs) const {
        return result < rhs.result;
    }

    bool CalculationNumberResults::operator<=(const CalculationNumberResults &rhs) const {
        return result <= rhs.result;
    }

    bool CalculationNumberResults::operator>=(const CalculationNumberResults &rhs) const {
        return result >= rhs.result;
    }

    bool CalculationNumberResults::operator==(const CalculationNumberResults &rhs) const {
        return result == rhs.result;
    }

    bool CalculationNumberResults::operator!=(const CalculationNumberResults &rhs) const {
        return result != rhs.result;
    }

    CalculationNumberResults::CalculationNumberResults(const int result_layers, const double result, string source) :
            result_layers(result_layers), result(result), source(std::move(source)) {
    }

    size_t CalculationNumberResults::operator()(const CalculationNumberResults &person) const {
        return std::hash<std::string>{}(person.source) ^ std::hash<double>{}(person.result) ^
               std::hash<int>{}(person.result_layers);
    }

    double CalculationNumberResults::getResult() const {
        return this->getResult_double();
    }

    CalculationNumberResults::~CalculationNumberResults() = default;

    size_t CalculationResults::operator()(CalculationResults &r) const {
        return std::hash<double>{}(r.getResult_double()) ^ std::hash<std::string>{}(r.getCalculationSourceName()) ^
               std::hash<int>{}(r.getResultLayers());
    }

    CalculationNumberResults operator+(CalculationNumberResults v1, CalculationNumberResults v2) {
        return {
                v1.getResultLayers() + v2.getResultLayers(),
                v1.getResult_double() + v2.getResult_double(),
                "(CalculationNumberResults." + v1.getCalculationSourceName() + " + CalculationNumberResults." +
                v2.getCalculationSourceName() + ')'
        };
    }

    CalculationNumberResults operator-(CalculationNumberResults v1, CalculationNumberResults v2) {
        return {
                v1.getResultLayers() + v2.getResultLayers(),
                v1.getResult_double() - v2.getResult_double(),
                "(CalculationNumberResults." + v1.getCalculationSourceName() + " + CalculationNumberResults." +
                v2.getCalculationSourceName() + ')'
        };
    }

    CalculationNumberResults operator*(CalculationNumberResults v1, CalculationNumberResults v2) {
        return {
                v1.getResultLayers() + v2.getResultLayers(),
                v1.getResult_double() * v2.getResult_double(),
                "(CalculationNumberResults." + v1.getCalculationSourceName() + " + CalculationNumberResults." +
                v2.getCalculationSourceName() + ')'
        };
    };

    CalculationNumberResults operator/(CalculationNumberResults v1, CalculationNumberResults v2) {
        return {
                v1.getResultLayers() + v2.getResultLayers(),
                v1.getResult_double() / v2.getResult_double(),
                "(CalculationNumberResults." + v1.getCalculationSourceName() + " + CalculationNumberResults." +
                v2.getCalculationSourceName() + ')'
        };
    }

    CalculationNumberResults operator<<(CalculationNumberResults v1, CalculationNumberResults v2) {
        return {
                v1.getResultLayers() + v2.getResultLayers(),
                v1.getResult_double() + v2.getResult_double(),
                "(CalculationNumberResults." + v1.getCalculationSourceName() + " + CalculationNumberResults." +
                v2.getCalculationSourceName() + ')'
        };
    }

    CalculationNumberResults operator>>(CalculationNumberResults v1, CalculationNumberResults v2) {
        return {
                v1.getResultLayers() + v2.getResultLayers(),
                v1.getResult_double() + v2.getResult_double(),
                "(CalculationNumberResults." + v1.getCalculationSourceName() + " + CalculationNumberResults." +
                v2.getCalculationSourceName() + ')'
        };
    }

    ostream &operator<<(ostream &out, const CalculationNumberResults *rhs) {
        return out << rhs->getResult_double();
    }

    ostream &operator<<(ostream &out, const CalculationNumberResults &rhs) {
        return out << rhs.getResult_double();
    }
}